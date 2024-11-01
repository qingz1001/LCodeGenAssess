#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t x1, y1, x2, y2;
    int top_y;
    int lower_x;
} Segment;

int cmp_int64(const void* a, const void* b) {
    int64_t va = *(int64_t*)a;
    int64_t vb = *(int64_t*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int cmp_segments(const void* a, const void* b) {
    Segment* sa = (Segment*)a;
    Segment* sb = (Segment*)b;
    if (sa->top_y != sb->top_y)
        return sb->top_y - sa->top_y;
    return 0;
}

int main(){
    int N;
    int64_t S;
    scanf("%d %lld", &N, &S);
    Segment* segments = (Segment*)malloc(sizeof(Segment)*N);
    int64_t* xs = (int64_t*)malloc(sizeof(int64_t)*(2*N +1));
    int cnt =0;
    for(int i=0;i<N;i++){
        scanf("%lld %lld %lld %lld", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
        xs[cnt++] = segments[i].x1;
        xs[cnt++] = segments[i].x2;
    }
    xs[cnt++] = S;
    qsort(xs, cnt, sizeof(int64_t), cmp_int64);
    int unique = 0;
    for(int i=1;i<cnt;i++){
        if(xs[i] != xs[unique]){
            unique++;
            xs[unique] = xs[i];
        }
    }
    unique++;
    // Map x to index
    // Preprocess segments
    for(int i=0;i<N;i++){
        segments[i].top_y = segments[i].y1 > segments[i].y2 ? segments[i].y1 : segments[i].y2;
        if(segments[i].y1 < segments[i].y2){
            segments[i].lower_x = segments[i].x1;
        }
        else{
            segments[i].lower_x = segments[i].x2;
        }
    }
    // Sort segments by top_y descending
    qsort(segments, N, sizeof(Segment), cmp_segments);
    // Initialize assign and parent
    int M = unique;
    int* assign = (int*)malloc(sizeof(int)*M);
    for(int i=0;i<M;i++) assign[i] = -1;
    int* parent = (int*)malloc(sizeof(int)*M);
    for(int i=0;i<M;i++) parent[i] = i;
    // Find function with path compression
    // Implemented iteratively
    #define find_set(x) ({ \
        int _x = (x); \
        while(parent[_x] != _x){ \
            parent[_x] = parent[parent[_x]]; \
            _x = parent[_x]; \
        } \
        _x; \
    })
    // Assign segments to x's
    for(int i=0;i<N;i++){
        int64_t min_x = segments[i].x1 < segments[i].x2 ? segments[i].x1 : segments[i].x2;
        int64_t max_x = segments[i].x1 > segments[i].x2 ? segments[i].x1 : segments[i].x2;
        // Find l: first x > min_x
        int l = 0, r = M;
        while(l < r){
            int m = l + (r - l)/2;
            if(xs[m] > min_x){
                r = m;
            }
            else{
                l = m +1;
            }
        }
        int left = l;
        // Find r: first x >= max_x
        l = 0; r = M;
        while(l < r){
            int m = l + (r - l)/2;
            if(xs[m] >= max_x){
                r = m;
            }
            else{
                l = m +1;
            }
        }
        int right = l;
        if(left >= right) continue;
        while(left < right){
            int pos = find_set(left);
            if(pos >= right) break;
            assign[pos] = i;
            parent[pos] = pos +1;
        }
    }
    // Precompute lower_x indices
    // No need, just keep lower_x as actual x
    // Find index of S
    int current_x = -1;
    for(int i=0;i<M;i++) if(xs[i] == S){current_x = i; break;}
    while(current_x != -1){
        if(assign[current_x] == -1){
            break;
        }
        int seg_idx = assign[current_x];
        // Find the lower_x
        int64_t new_x = segments[seg_idx].lower_x;
        // Find the index of new_x
        int l = 0, r = M;
        while(l < r){
            int m = l + (r - l)/2;
            if(xs[m] >= new_x){
                r = m;
            }
            else{
                l = m +1;
            }
        }
        if(l < M && xs[l] == new_x){
            current_x = l;
        }
        else{
            current_x = -1;
        }
    }
    if(current_x == -1){
        printf("%lld\n", S);
    }
    else{
        printf("%lld\n", xs[current_x]);
    }
    free(segments);
    free(xs);
    free(assign);
    free(parent);
    return 0;
}