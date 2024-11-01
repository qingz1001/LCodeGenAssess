#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long t;
} Drop;

int compare(const void *a, const void *b) {
    Drop *da = (Drop *)a;
    Drop *db = (Drop *)b;
    if (da->x != db->x)
        return (da->x < db->x) ? -1 : 1;
    return 0;
}

int is_possible(Drop *drops, int N, long long W, long long D) {
    int left = 0;
    int min_head = 0, min_tail = 0;
    int max_head = 0, max_tail = 0;
    long long *min_deque = (long long *)malloc(N * sizeof(long long));
    long long *max_deque = (long long *)malloc(N * sizeof(long long));
    for(int right = 0; right < N; right++) {
        while(min_tail > min_head && drops[min_deque[min_tail-1]].t >= drops[right].t)
            min_tail--;
        min_deque[min_tail++] = right;
        while(max_tail > max_head && drops[max_deque[max_tail-1]].t <= drops[right].t)
            max_tail--;
        max_deque[max_tail++] = right;
        while(drops[right].x - drops[left].x > W) {
            if(min_deque[min_head] == left) min_head++;
            if(max_deque[max_head] == left) max_head++;
            left++;
        }
        if(max_tail > max_head && drops[max_deque[max_head]].t - drops[min_deque[min_head]].t >= D){
            free(min_deque);
            free(max_deque);
            return 1;
        }
    }
    free(min_deque);
    free(max_deque);
    return 0;
}

int main(){
    int N;
    long long D;
    scanf("%d %lld", &N, &D);
    Drop *drops = (Drop *)malloc(N * sizeof(Drop));
    for(int i = 0; i < N; i++) {
        scanf("%lld %lld", &drops[i].x, &drops[i].t);
    }
    qsort(drops, N, sizeof(Drop), compare);
    long long l = 0, r = 1000000, ans = -1;
    while(l <= r){
        long long mid = l + (r - l) / 2;
        if(is_possible(drops, N, mid, D)){
            ans = mid;
            r = mid -1;
        }
        else{
            l = mid +1;
        }
    }
    printf("%lld\n", ans);
    free(drops);
    return 0;
}