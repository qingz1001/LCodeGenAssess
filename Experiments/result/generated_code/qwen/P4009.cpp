#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 101

int N, K, A, B, C;
int grid[MAXN][MAXN];
int dp[MAXN][MAXN][K + 1];

void init() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = INT_MAX / 2;
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    init();
    dp[1][1][K] = 0;

    for (int k = 0; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dp[i][j][k] == INT_MAX / 2) continue;

                // Move right
                if (j + 1 <= N) {
                    dp[i][j + 1][k - 1] = min(dp[i][j + 1][k - 1], dp[i][j][k] + (i != 1 || j + 1 != 1) * B);
                }

                // Move down
                if (i + 1 <= N) {
                    dp[i + 1][j][k - 1] = min(dp[i + 1][j][k - 1], dp[i][j][k] + (i + 1 != 1 || j != 1) * B);
                }

                // Refuel at current position
                if (grid[i][j]) {
                    dp[i][j][K] = min(dp[i][j][K], dp[i][j][k] + A);
                }

                // Add oil station at current position
                if (!grid[i][j]) {
                    dp[i][j][K] = min(dp[i][j][K], dp[i][j][k] + C);
                }
            }
        }
    }

    int result = INT_MAX / 2;
    for (int k = 0; k <= K; k++) {
        result = min(result, dp[N][N][k]);
    }

    printf("%d\n", result);

    return 0;
}