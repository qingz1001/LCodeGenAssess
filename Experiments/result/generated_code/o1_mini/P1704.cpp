#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef struct {
    int day;
    int c;
} Point;

int cmp_point(const void* a, const void* b){
    Point* pa = (Point*)a;
    Point* pb = (Point*)b;
    if(pa->day < pb->day) return -1;
    if(pa->day > pb->day) return 1;
    return 0;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    int* p = (int*)malloc(K * sizeof(int));
    int* required = (int*)calloc(N+1, sizeof(int));
    for(int i=0;i<K;i++) { scanf("%d", &p[i]); required[p[i]]=1; }
    int* c = (int*)malloc((N+1)*sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &c[i]);
    Point* req = (Point*)malloc(K * sizeof(Point));
    for(int i=0;i<K;i++) { req[i].day = p[i]; req[i].c = c[p[i]]; }
    qsort(req, K, sizeof(Point), cmp_point);
    for(int i=1;i<K;i++) {
        if(req[i].c <= req[i-1].c){
            printf("impossible");
            return 0;
        }
    }
    // Initialize
    ll res = K;
    int prev_day = 0;
    int prev_c = 0;
    // Binary search helper
    int* tails = (int*)malloc((N+1)*sizeof(int));
    int size = 0;
    int idx = 0;
    for(int i=0;i<=K;i++){
        int left, right;
        int start, end;
        if(i < K){
            start = prev_day +1;
            end = req[i].day -1;
        }
        else{
            start = prev_day +1;
            end = N;
        }
        if(start <= end){
            // Collect valid c's
            // Find LIS with c > prev_c and < req[i].c
            // Here we can iterate and use standard LIS
            size = 0;
            for(int j=start; j<=end; j++){
                if(c[j] > prev_c && (i < K ? c[j] < req[i].c : 1)){
                    // Binary search in tails
                    left = 0;
                    right = size;
                    while(left < right){
                        int mid = left + (right - left)/2;
                        if(tails[mid] < c[j]) left = mid +1;
                        else right = mid;
                    }
                    tails[left] = c[j];
                    if(left == size) size++;
                }
            }
            res += size;
        }
        if(i < K){
            prev_day = req[i].day;
            prev_c = req[i].c;
        }
    }
    free(tails);
    free(req);
    free(c);
    free(required);
    free(p);
    printf("%lld", res);
}