#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

int main(){
    int N,K;
    scanf("%d %d", &N, &K);
    ll *D = (ll*)malloc((N+1)*sizeof(ll));
    D[1] = 0;
    for(int i=2;i<=N;i++) scanf("%lld", &D[i]);
    ll *C = (ll*)malloc((N+1)*sizeof(ll));
    for(int i=1;i<=N;i++) scanf("%lld", &C[i]);
    ll *S = (ll*)malloc((N+1)*sizeof(ll));
    for(int i=1;i<=N;i++) scanf("%lld", &S[i]);
    ll *W = (ll*)malloc((N+1)*sizeof(ll));
    for(int i=1;i<=N;i++) scanf("%lld", &W[i]);
    // Positions
    ll *x = (ll*)malloc((N+1)*sizeof(ll));
    x[1] = 0;
    for(int i=2;i<=N;i++) x[i] = D[i];
    // Precompute l[j] and r[j]
    int *l = (int*)malloc((N+1)*sizeof(int));
    int *r = (int*)malloc((N+1)*sizeof(int));
    for(int j=1;j<=N;j++){
        // l[j]: first village >= x[j] - S[j]
        ll left_pos = x[j] - S[j];
        if(left_pos < 0) left_pos = 0;
        // Binary search for first i where x[i] >= left_pos
        int low=1, high=N, pos=1;
        while(low <= high){
            int mid = (low + high)/2;
            if(x[mid] >= left_pos){
                pos = mid;
                high = mid -1;
            }
            else{
                low = mid +1;
            }
        }
        l[j] = pos;
        // r[j]: last village <= x[j] + S[j]
        ll right_pos = x[j] + S[j];
        // Binary search for last i where x[i] <= right_pos
        low=1; high=N; pos=N;
        while(low <= high){
            int mid = (low + high)/2;
            if(x[mid] <= right_pos){
                pos = mid;
                low = mid +1;
            }
            else{
                high = mid -1;
            }
        }
        r[j] = pos;
    }
    // Precompute prefix sum of W
    ll *prefixW = (ll*)malloc((N+2)*sizeof(ll));
    prefixW[0] = 0;
    for(int i=1;i<=N;i++) prefixW[i] = prefixW[i-1] + W[i];
    // Initialize DP
    ll INF = 1e18;
    ll **dp = (ll**)malloc((K+1)*sizeof(ll*));
    for(int k=0;k<=K;k++) {
        dp[k] = (ll*)malloc((N+1)*sizeof(ll));
        for(int i=0;i<=N;i++) dp[k][i] = INF;
    }
    // dp[0][i] = sum W[1..i]
    for(int i=0;i<=N;i++) {
        if(i ==0) dp[0][i] = 0;
        else dp[0][i] = prefixW[i];
    }
    // DP
    for(int k=1;k<=K;k++){
        // Initialize dp[k][i] to INF
        for(int i=0;i<=N;i++) dp[k][i] = dp[k][i] < INF ? dp[k][i] : INF;
        // Place base stations
        for(int j=1;j<=N;j++){
            if(l[j]-1 >=0 && r[j]<=N){
                if(dp[k-1][l[j]-1] + C[j] < dp[k][r[j]]){
                    dp[k][r[j]] = dp[k-1][l[j]-1] + C[j];
                }
            }
        }
        // Pay penalties
        for(int i=1;i<=N;i++){
            if(dp[k][i-1] + W[i] < dp[k][i]){
                dp[k][i] = dp[k][i-1] + W[i];
            }
        }
    }
    // Find the minimum among dp[0..K][N]
    ll res = INF;
    for(int k=0;k<=K;k++) {
        if(dp[k][N] < res){
            res = dp[k][N];
        }
    }
    printf("%lld\n", res);
    // Free memory
    free(D);
    free(C);
    free(S);
    free(W);
    free(x);
    free(l);
    free(r);
    free(prefixW);
    for(int k=0;k<=K;k++) free(dp[k]);
    free(dp);
    return 0;
}