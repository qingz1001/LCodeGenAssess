#include <stdio.h>
#define MOD 1000000007

int R, C, K;
int grid[105][105];
long long dp[105][105];

int main() {
    scanf("%d%d%d", &R, &C, &K);
    
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    dp[1][1] = 1;
    
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (i == 1 && j == 1) continue;
            
            for (int k = 1; k < i; k++) {
                for (int l = 1; l < j; l++) {
                    if (grid[i][j] != grid[k][l]) {
                        dp[i][j] = (dp[i][j] + dp[k][l]) % MOD;
                    }
                }
            }
        }
    }
    
    printf("%lld\n", dp[R][C]);
    
    return 0;
}