#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 15
#define MAXM 15

int n, m;
char matrix[MAXN][MAXM];
int dp[MAXN][MAXM][1 << MAXM][2];

int solve() {
    memset(dp, 0, sizeof(dp));
    
    int full_mask = (1 << m) - 1;
    dp[0][m][0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            dp[i][0][j][0] = dp[i-1][m][j][0];
            dp[i][0][j][1] = dp[i-1][m][j][1];
        }
        
        for (int j = 1; j <= m; j++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (matrix[i-1][j-1] == '1' || matrix[i-1][j-1] == '.') {
                    int new_mask = mask | (1 << (j-1));
                    dp[i][j][new_mask][1] = (dp[i][j][new_mask][1] + dp[i][j-1][mask][0]) % MOD;
                    
                    if (j > 1 && !(mask & (1 << (j-2))))
                        dp[i][j][new_mask][1] = (dp[i][j][new_mask][1] + dp[i][j-1][mask][1]) % MOD;
                    
                    if (i > 1 && !(mask & (1 << (j-1))))
                        dp[i][j][new_mask][1] = (dp[i][j][new_mask][1] + dp[i][j-1][mask][1]) % MOD;
                }
                
                if (matrix[i-1][j-1] == '0' || matrix[i-1][j-1] == '.') {
                    dp[i][j][mask][0] = (dp[i][j][mask][0] + dp[i][j-1][mask][0]) % MOD;
                    dp[i][j][mask][0] = (dp[i][j][mask][0] + dp[i][j-1][mask][1]) % MOD;
                }
            }
        }
    }
    
    int result = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        result = (result + dp[n][m][mask][0]) % MOD;
        result = (result + dp[n][m][mask][1]) % MOD;
    }
    
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    
    printf("%d\n", solve());
    
    return 0;
}