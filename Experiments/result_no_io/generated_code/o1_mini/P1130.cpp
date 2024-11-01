#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Allocate memory for cost
    ll **cost = (ll**)malloc(M * sizeof(ll*));
    for(int i=0;i<M;i++) {
        cost[i] = (ll*)malloc(N * sizeof(ll));
        for(int j=0;j<N;j++) {
            scanf("%lld", &cost[i][j]);
        }
    }
    
    // Allocate memory for DP
    ll *dp_prev = (ll*)malloc(M * sizeof(ll));
    ll *dp_current = (ll*)malloc(M * sizeof(ll));
    
    // Initialize dp_prev with first step
    for(int k=0; k<M; k++) {
        dp_prev[k] = cost[k][0];
    }
    
    // Iterate over steps
    for(int j=1; j<N; j++) {
        for(int k=0; k<M; k++) {
            int k_prev = (k - 1 + M) % M;
            if(dp_prev[k] < dp_prev[k_prev]) {
                dp_current[k] = dp_prev[k] + cost[k][j];
            }
            else {
                dp_current[k] = dp_prev[k_prev] + cost[k][j];
            }
        }
        // Swap dp_prev and dp_current
        ll *temp = dp_prev;
        dp_prev = dp_current;
        dp_current = temp;
    }
    
    // Find minimum in dp_prev
    ll min_val = dp_prev[0];
    for(int k=1; k<M; k++) {
        if(dp_prev[k] < min_val){
            min_val = dp_prev[k];
        }
    }
    
    printf("%lld\n", min_val);
    
    // Free memory
    for(int i=0;i<M;i++) {
        free(cost[i]);
    }
    free(cost);
    free(dp_prev);
    free(dp_current);
    
    return 0;
}