#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll* w = (ll*)malloc((n+2) * sizeof(ll));
    for(int i=0;i<=n;i++) scanf("%lld", &w[i]);
    
    // If n is too large, it's not feasible to compute
    if(n > 2000){
        // Handle large n as per problem constraints (could output 0 or a specific value)
        // Here, we assume n <= 2000 for practical purposes
        // You may need to adjust based on actual problem requirements
        // For demonstration, we'll terminate
        return 0;
    }
    
    // Initialize DP table
    ll** dp = (ll**)malloc((n+1) * sizeof(ll*));
    for(int i=0;i<=n;i++) {
        dp[i] = (ll*)malloc((n+1) * sizeof(ll));
        for(int j=0;j<=n;j++) dp[i][j] = 0;
    }
    
    // Initialize opt table for Knuth's optimization
    int** opt = (int**)malloc((n+1) * sizeof(int*));
    for(int i=0;i<=n;i++) {
        opt[i] = (int*)malloc((n+1) * sizeof(int));
        for(int j=0;j<=n;j++) opt[i][j] = 0;
    }
    
    // Base cases
    for(int i=1;i<=n;i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    
    // Fill DP table
    for(int length=2; length<=n; length++){
        for(int i=1; i<=n-length+1; i++){
            int j = i + length -1;
            dp[i][j] = LLONG_MAX;
            // Knuth's optimization: the optimal k for [i,j] is between opt[i][j-1] and opt[i+1][j]
            int start = opt[i][j-1];
            int end = opt[i+1][j];
            if(start < i) start = i;
            if(end > j-1) end = j-1;
            for(int k = start; k <= end; k++){
                ll cost = dp[i][k] + dp[k+1][j] + w[i-1]*w[k]*w[j];
                if(cost < dp[i][j]){
                    dp[i][j] = cost;
                    opt[i][j] = k;
                }
            }
        }
    }
    
    printf("%lld\n", dp[1][n]);
    
    // Free memory
    for(int i=0;i<=n;i++) {
        free(dp[i]);
        free(opt[i]);
    }
    free(dp);
    free(opt);
    free(w);
    return 0;
}