#include <stdio.h>
#include <stdlib.h>
#include <longlong.h>
#include <limits.h>

typedef struct {
    long long x;
    long long y;
    int id;
} Point;

int cmp_x_asc_y_asc(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    return 0;
}

int cmp_x_asc_y_desc(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if (pa->y != pb->y)
        return (pa->y > pb->y) ? -1 : 1;
    return 0;
}

int cmp_y_asc_x_asc(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    return 0;
}

int cmp_y_asc_x_desc(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    if (pa->x != pb->x)
        return (pa->x > pb->x) ? -1 : 1;
    return 0;
}

long long absll(long long a) {
    return a < 0 ? -a : a;
}

int main(){
    int N;
    scanf("%d", &N);
    Point *points = (Point*)malloc(sizeof(Point)*N);
    for(int i=0;i<N;i++){
        scanf("%lld %lld", &points[i].x, &points[i].y);
        points[i].id = i;
    }
    // Compute max and min of u = x+y and v = x-y
    long long max_u = LLONG_MIN, min_u = LLONG_MAX;
    long long max_v = LLONG_MIN, min_v = LLONG_MAX;
    for(int i=0;i<N;i++){
        long long u = points[i].x + points[i].y;
        long long v = points[i].x - points[i].y;
        if(u > max_u) max_u = u;
        if(u < min_u) min_u = u;
        if(v > max_v) max_v = v;
        if(v < min_v) min_v = v;
    }
    // Initialize min_dist
    long long *min_dist = (long long*)malloc(sizeof(long long)*N);
    for(int i=0;i<N;i++) min_dist[i] = LLONG_MAX;
    // Temporary array for sorting
    Point *sorted = (Point*)malloc(sizeof(Point)*N);
    // Sort by x asc, y asc
    for(int i=0;i<N;i++) sorted[i] = points[i];
    qsort(sorted, N, sizeof(Point), cmp_x_asc_y_asc);
    for(int i=0;i<N;i++){
        if(i > 0){
            long long d = absll(sorted[i].x - sorted[i-1].x) + absll(sorted[i].y - sorted[i-1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
        if(i < N-1){
            long long d = absll(sorted[i].x - sorted[i+1].x) + absll(sorted[i].y - sorted[i+1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
    }
    // Sort by x asc, y desc
    for(int i=0;i<N;i++) sorted[i] = points[i];
    qsort(sorted, N, sizeof(Point), cmp_x_asc_y_desc);
    for(int i=0;i<N;i++){
        if(i > 0){
            long long d = absll(sorted[i].x - sorted[i-1].x) + absll(sorted[i].y - sorted[i-1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
        if(i < N-1){
            long long d = absll(sorted[i].x - sorted[i+1].x) + absll(sorted[i].y - sorted[i+1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
    }
    // Sort by y asc, x asc
    for(int i=0;i<N;i++) sorted[i] = points[i];
    qsort(sorted, N, sizeof(Point), cmp_y_asc_x_asc);
    for(int i=0;i<N;i++){
        if(i > 0){
            long long d = absll(sorted[i].x - sorted[i-1].x) + absll(sorted[i].y - sorted[i-1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
        if(i < N-1){
            long long d = absll(sorted[i].x - sorted[i+1].x) + absll(sorted[i].y - sorted[i+1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
    }
    // Sort by y asc, x desc
    for(int i=0;i<N;i++) sorted[i] = points[i];
    qsort(sorted, N, sizeof(Point), cmp_y_asc_x_desc);
    for(int i=0;i<N;i++){
        if(i > 0){
            long long d = absll(sorted[i].x - sorted[i-1].x) + absll(sorted[i].y - sorted[i-1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
        if(i < N-1){
            long long d = absll(sorted[i].x - sorted[i+1].x) + absll(sorted[i].y - sorted[i+1].y);
            if(d < min_dist[sorted[i].id]) min_dist[sorted[i].id] = d;
        }
    }
    // Now compute max_dist and delta
    long long result = LLONG_MAX;
    for(int i=0;i<N;i++){
        long long u = points[i].x + points[i].y;
        long long v = points[i].x - points[i].y;
        long long max_dist = absll(u - max_u);
        if(absll(u - min_u) > max_dist) max_dist = absll(u - min_u);
        if(absll(v - max_v) > max_dist) max_dist = absll(v - max_v);
        if(absll(v - min_v) > max_dist) max_dist = absll(v - min_v);
        long long delta = max_dist - min_dist[i];
        if(delta < result) result = delta;
    }
    printf("%lld\n", result);
    free(points);
    free(sorted);
    free(min_dist);
    return 0;
}