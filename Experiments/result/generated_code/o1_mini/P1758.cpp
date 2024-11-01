#include <stdio.h>
#include <string.h>

#define MOD 1024523

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    char S[501], T[501];
    scanf("%s", S);
    scanf("%s", T);
    
    // Initialize DP table
    int dp[501][501];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    // Initialize first column
    for(int i=1;i<=n;i++){
        dp[i][0] = dp[i-1][0];
    }
    
    // Initialize first row
    for(int j=1;j<=m;j++){
        dp[0][j] = dp[0][j-1];
    }
    
    // Fill the DP table
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(S[i-1] == T[j-1]){
                long long temp = ( (long long)dp[i-1][j] + (long long)dp[i][j-1] ) % MOD;
                temp = (temp + 2LL * dp[i-1][j-1]) % MOD;
                dp[i][j] = (int)temp;
            }
            else{
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
            }
        }
    }
    
    printf("%d\n", dp[n][m]);
    return 0;
}