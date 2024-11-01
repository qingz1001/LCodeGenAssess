#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

int main(){
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    
    // Allocate roads[n+1][m+1]
    // To save memory and access faster, use 1-based indexing
    int **roads = (int **)malloc((n +1) * sizeof(int *));
    for(int i=1;i<=n;i++){
        roads[i] = (int *)malloc((m +1) * sizeof(int));
        for(int j=1;j<=m;j++){
            scanf("%d", &roads[i][j]);
        }
    }
    
    // Read cost[n]
    int *cost = (int *)malloc((n +1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &cost[i]);
    
    // Initialize dp[m+1]
    ll *dp = (ll *)malloc((m +1) * sizeof(ll));
    for(int i=0;i<=m;i++) dp[i] = LLONG_MIN;
    dp[0] = 0;
    
    // Allocate sum[n+1]
    ll *sum = (ll *)malloc((n +1) * sizeof(ll));
    
    for(int s=1;s<=p;s++){
        // Initialize sum[i] for t=s
        for(int i=1;i<=n;i++) sum[i] =0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<s;j++){
                int road_id = ((i + j -1) %n) +1;
                int time = 1 + j;
                if(time > m) break;
                sum[i] += roads[road_id][time];
            }
        }
        
        for(int t=s; t<=m; t++){
            if(t > s){
                for(int i=1;i<=n;i++){
                    int road_in_id = ((i + s -1) %n) +1;
                    int road_out_id = i;
                    int time_in = t;
                    int time_out = t - s;
                    sum[i] += roads[road_in_id][time_in] - roads[road_out_id][time_out];
                }
            }
            // Find max_i (sum[i] - cost[i])
            ll max_val = LLONG_MIN;
            for(int i=1;i<=n;i++){
                ll tmp = sum[i] - (ll)cost[i];
                if(tmp > max_val) max_val = tmp;
            }
            // Update dp[t]
            if(dp[t -s] != LLONG_MIN){
                ll candidate = dp[t -s] + max_val;
                if(candidate > dp[t]) dp[t] = candidate;
            }
        }
    }
    
    // Find the answer
    ll answer = dp[m];
    printf("%lld\n", answer);
    
    // Free memory
    for(int i=1;i<=n;i++) free(roads[i]);
    free(roads);
    free(cost);
    free(dp);
    free(sum);
    
    return 0;
}