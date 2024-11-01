#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int R, C, K;
    scanf("%d%d%d", &R, &C, &K);

    int **grid = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; i++) {
        grid[i] = (int *)malloc(C * sizeof(int));
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // dp[i][j] 表示从左上角跳到 (i, j) 的方案数
    int **dp = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; i++) {
        dp[i] = (int *)calloc(C, sizeof(int));
    }

    // 初始化起点
    dp[0][0] = 1;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;

            // 从上方跳下来
            if (i > 0) {
                for (int k = 0; k < i; k++) {
                    if (grid[k][j] != grid[i][j]) {
                        dp[i][j] = (dp[i][j] + dp[k][j]) % MOD;
                    }
                }
            }

            // 从左方跳过来
            if (j > 0) {
                for (int k = 0; k < j; k++) {
                    if (grid[i][k] != grid[i][j]) {
                        dp[i][j] = (dp[i][j] + dp[i][k]) % MOD;
                    }
                }
            }
        }
    }

    int result = dp[R-1][C-1];
    printf("%d\n", result);

    for (int i = 0; i < R; i++) {
        free(grid[i]);
        free(dp[i]);
    }
    free(grid);
    free(dp);

    return 0;
}