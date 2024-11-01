#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    int *scores = (int*)malloc(N * sizeof(int));
    for(int i=0; i<N; i++) scanf("%d", &scores[i]);

    ll *suff_sum = (ll*)malloc((N+1) * sizeof(ll));
    int *suff_min = (int*)malloc((N+1) * sizeof(int));

    suff_sum[N] = 0;
    suff_min[N] = INT32_MAX;
    for(int K=N-1; K>=0; K--){
        suff_sum[K] = suff_sum[K+1] + scores[K];
        suff_min[K] = scores[K] < suff_min[K+1] ? scores[K] : suff_min[K+1];
    }

    ll max_S = suff_sum[1] - suff_min[1];
    int max_D = N-2;
    for(int K=2; K<=N-2; K++){
        ll S = suff_sum[K] - suff_min[K];
        int D = N-K-1;
        if(S * max_D > max_S * (ll)D){
            max_S = S;
            max_D = D;
        }
    }

    for(int K=1; K<=N-2; K++){
        ll S = suff_sum[K] - suff_min[K];
        int D = N-K-1;
        if(S * max_D == max_S * (ll)D){
            printf("%d\n", K);
        }
    }

    free(scores);
    free(suff_sum);
    free(suff_min);
    return 0;
}