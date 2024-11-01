#include <stdio.h>
#include <string.h>

#define MOD 1024523
#define MAX 501

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char S[MAX], T[MAX];
    scanf("%s %s", S, T);
    
    // Initialize DP table
    long long dp[MAX][MAX];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i < n){
                dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;
            }
            if(j < m){
                dp[i][j+1] = (dp[i][j+1] + dp[i][j]) % MOD;
            }
            if(i < n && j < m && S[i] == T[j]){
                dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j] * 2) % MOD;
            }
        }
    }
    
    printf("%lld\n", dp[n][m]%MOD);
    return 0;
}