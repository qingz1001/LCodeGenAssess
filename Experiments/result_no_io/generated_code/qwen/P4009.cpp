#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 10

int N, K, A, B, C;
int grid[MAX_N][MAX_N];
int dp[MAX_N + 1][MAX_N + 1][K + 1];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Initialize DP table with infinity
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = INT_MAX;
            }
        }
    }

    // Starting point
    dp[1][1][K] = 0;

    for (int k = 0; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dp[i][j][k] == INT_MAX) continue;

                // Move right
                if (j < N && k >= 1) {
                    int cost = (i == 1) ? 0 : B;
                    dp[i][j + 1][k - 1] = min(dp[i][j + 1][k - 1], dp[i][j][k] + cost);
                }

                // Move down
                if (i < N && k >= 1) {
                    int cost = (j == 1) ? 0 : B;
                    dp[i + 1][j][k - 1] = min(dp[i + 1][j][k - 1], dp[i][j][k] + cost);
                }

                // Refuel at current position
                if (grid[i][j] == 1) {
                    dp[i][j][K] = min(dp[i][j][K], dp[i][j][k] + A);
                } else {
                    dp[i][j][K - 1] = min(dp[i][j][K - 1], dp[i][j][k] + A);
                }
            }
        }
    }

    int result = INT_MAX;
    for (int k = 0; k <= K; k++) {
        result = min(result, dp[N][N][k]);
    }

    printf("%d\n", result);

    return 0;
}