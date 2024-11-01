#include <stdio.h>
#define MOD 1000000007

int main() {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);
    
    int dp[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i > 0 && dp[i-1][j] != 0 && dp[i][j] == 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }
            if (j > 0 && dp[i][j-1] != 0 && dp[i][j] == 0) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }
    
    printf("%d\n", dp[R-1][C-1]);
    
    return 0;
}