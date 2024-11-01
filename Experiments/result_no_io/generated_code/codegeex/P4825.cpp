#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    int R, C, K;
    scanf("%d%d%d", &R, &C, &K);
    
    int grid[101][101];
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    long long dp[101][101][1001];
    memset(dp, 0, sizeof(dp));
    dp[1][1][grid[1][1]] = 1;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            for (int x = 1; x <= K; x++) {
                if (dp[i][j][x] == 0) continue;
                for (int a = 1; a <= R; a++) {
                    for (int b = 1; b <= C; b++) {
                        if (a <= i || b <= j) continue;
                        if (grid[a][b] == x) continue;
                        dp[a][b][grid[a][b]] = (dp[a][b][grid[a][b]] + dp[i][j][x]) % MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", dp[R][C][grid[R][C]]);
    return 0;
}