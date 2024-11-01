#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);

    int grid[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int dp[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (int x = i + 1; x < R; x++) {
                for (int y = j + 1; y < C; y++) {
                    if (grid[i][j] != grid[x][y]) {
                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", dp[R-1][C-1]);

    return 0;
}