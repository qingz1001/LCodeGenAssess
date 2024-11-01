#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int d1;
    int d2;
} Missile;

int compare(const void* a, const void* b){
    Missile* m1 = (Missile*)a;
    Missile* m2 = (Missile*)b;
    if(m1->d1 != m2->d1){
        return m1->d1 - m2->d1;
    }
    return m1->d2 - m2->d2;
}

int main(){
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int N;
    scanf("%d", &N);
    Missile* missiles = (Missile*)malloc(N * sizeof(Missile));
    for(int i = 0; i < N; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        int dx1 = x - x1;
        int dy1 = y - y1;
        missiles[i].d1 = dx1 * dx1 + dy1 * dy1;
        int dx2 = x - x2;
        int dy2 = y - y2;
        missiles[i].d2 = dx2 * dx2 + dy2 * dy2;
    }
    qsort(missiles, N, sizeof(Missile), compare);
    // Compute suffix max for d2
    int* suffix_max = (int*)malloc(N * sizeof(int));
    if(N > 0){
        suffix_max[N-1] = missiles[N-1].d2;
        for(int i = N-2; i >= 0; i--){
            if(missiles[i].d2 > suffix_max[i+1]){
                suffix_max[i] = missiles[i].d2;
            }
            else{
                suffix_max[i] = suffix_max[i+1];
            }
        }
    }
    // Iterate over k from 0 to N
    ll min_cost = (ll)1e18;
    for(int k = 0; k <= N; k++){
        int r1 = 0;
        if(k > 0){
            r1 = missiles[k-1].d1;
        }
        int r2 = 0;
        if(k < N){
            r2 = suffix_max[k];
        }
        ll cost = (ll)r1 + (ll)r2;
        if(cost < min_cost){
            min_cost = cost;
        }
    }
    printf("%lld\n", min_cost);
    free(missiles);
    free(suffix_max);
    return 0;
}