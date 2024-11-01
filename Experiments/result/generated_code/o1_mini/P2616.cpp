#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define INF 100000000000LL

typedef struct {
    int X;
    int F;
    int C;
} Store;

int cmp_store(const void *a, const void *b) {
    Store *s1 = (Store*)a;
    Store *s2 = (Store*)b;
    if (s1->X != s2->X)
        return s1->X - s2->X;
    return 0;
}

int main(){
    int K, E, N;
    scanf("%d %d %d", &K, &E, &N);
    Store stores[N+1];
    for(int i=0;i<N;i++) {
        scanf("%d %d %d", &stores[i].X, &stores[i].F, &stores[i].C);
    }
    // Add the end position
    stores[N].X = E;
    stores[N].F = 0;
    stores[N].C = 0;
    int S = N+1;
    qsort(stores, S, sizeof(Store), cmp_store);
    // Initialize DP
    ll dp_prev[K+1];
    for(int j=0;j<=K;j++) dp_prev[j] = INF;
    dp_prev[0] = 0;
    for(int i=0;i<S-1;i++){
        ll dp_curr[K+1];
        for(int j=0; j<=K; j++) dp_curr[j] = INF;
        int distance = stores[i+1].X - stores[i].X;
        for(int j=0; j<=K; j++) {
            if(dp_prev[j] == INF) continue;
            // At store i, buy t from 0 to F_i, but not exceed K
            int max_t = stores[i].F;
            if(j + max_t > K) max_t = K - j;
            for(int t=0; t<=max_t; t++){
                int next_j = j + t;
                ll cost = dp_prev[j] + (ll)t * stores[i].C;
                if(cost < INF){
                    ll total_cost = cost + (ll)distance * next_j;
                    if(total_cost < dp_curr[next_j]){
                        dp_curr[next_j] = total_cost;
                    }
                }
            }
        }
        // Update dp_prev
        for(int j=0; j<=K; j++) dp_prev[j] = dp_curr[j];
    }
    printf("%lld\n", dp_prev[K]);
    return 0;
}