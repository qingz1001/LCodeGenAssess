#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    int *scores = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &scores[i]);

    // Compute prefix sums
    ll *prefix_sum = (ll*)malloc((N+1) * sizeof(ll));
    prefix_sum[0] = 0;
    for(int i=0;i<N;i++) prefix_sum[i+1] = prefix_sum[i] + scores[i];

    // Compute suffix minimums
    int *suff_min = (int*)malloc(N * sizeof(int));
    suff_min[N-1] = scores[N-1];
    for(int i=N-2;i>=0;i--) {
        if(scores[i] < suff_min[i+1]) suff_min[i] = scores[i];
        else suff_min[i] = suff_min[i+1];
    }

    // Initialize best average with K=1
    int K;
    K = 1;
    ll sum_remaining = prefix_sum[N] - prefix_sum[K];
    int min_remaining = suff_min[K];
    ll best_A = sum_remaining - min_remaining;
    ll best_D = N - K -1;

    // To store the list of best K's
    int *best_Ks = (int*)malloc((N-1) * sizeof(int));
    int count = 1;
    best_Ks[0] = K;

    for(K=2; K<=N-2; K++){
        sum_remaining = prefix_sum[N] - prefix_sum[K];
        min_remaining = suff_min[K];
        ll A_new = sum_remaining - min_remaining;
        ll D_new = N - K -1;

        // Compare A_new/D_new with best_A/best_D
        // To avoid floating point, compare A_new * best_D vs best_A * D_new
        __int128 lhs = (__int128)A_new * best_D;
        __int128 rhs = (__int128)best_A * D_new;

        if(lhs > rhs){
            best_A = A_new;
            best_D = D_new;
            count = 1;
            best_Ks[0] = K;
        }
        else if(lhs == rhs){
            best_Ks[count++] = K;
        }
    }

    for(int i=0;i<count;i++) printf("%d\n", best_Ks[i]);

    free(scores);
    free(prefix_sum);
    free(suff_min);
    free(best_Ks);
    return 0;
}