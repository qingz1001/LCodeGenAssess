#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);

    int **grid = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; i++) {
        grid[i] = (int *)malloc(C * sizeof(int));
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    long long **dp = (long long **)malloc((R + 1) * sizeof(long long *));
    for (int i = 0; i <= R; i++) {
        dp[i] = (long long *)calloc((C + 1), sizeof(long long));
    }

    dp[1][1] = 1;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (i > 1 && grid[i - 1][j] != grid[i][j]) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            if (j > 1 && grid[i][j - 1] != grid[i][j]) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    printf("%lld\n", dp[R][C]);

    for (int i = 0; i <= R; i++) {
        free(dp[i]);
    }
    free(dp);
    for (int i = 0; i < R; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}