#include <stdio.h>
#include <stdlib.h>

#define MAX_N 150
#define MAX_M 500

int dp[MAX_N][MAX_M];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &dp[i][j]);
        }
    }

    // Initialize DP table
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] += (i > 0 ? dp[i-1][j] : 0) + (j > 0 ? dp[i][j-1] : 0) - (i > 0 && j > 0 ? dp[i-1][j-1] : 0);
        }
    }

    // Calculate the maximum luckiness for 'N', 'O', and 'I'
    int max_luckiness = -2000000000;
    for (int i = 2; i < n - 1; ++i) {
        for (int j = 2; j < m - 2; ++j) {
            // N shape
            if (dp[i][j] - dp[i-1][j] - dp[i][j-1] + dp[i-1][j-1] >= 0 &&
                dp[i][j] - dp[i-2][j] - dp[i][j-1] + dp[i-2][j-1] >= 0 &&
                dp[i][j] - dp[i-1][j+1] - dp[i][j-1] + dp[i-1][j-2] >= 0 &&
                dp[i][j] - dp[i-1][j] - dp[i-1][j-2] + dp[i-2][j-2] >= 0 &&
                dp[i][j] - dp[i-2][j] - dp[i-1][j-2] + dp[i-2][j-3] >= 0 &&
                dp[i][j] - dp[i-1][j+1] - dp[i-1][j-2] + dp[i-2][j-3] >= 0) {
                max_luckiness = fmax(max_luckiness, dp[i][j] - dp[i-2][j] - dp[i][j-1] + dp[i-2][j-2]);
            }

            // O shape
            if (dp[i][j] - dp[i-2][j] - dp[i][j-2] + dp[i-2][j-2] >= 0 &&
                dp[i][j] - dp[i-2][j] - dp[i][j-1] + dp[i-2][j-1] >= 0 &&
                dp[i][j] - dp[i-1][j] - dp[i-1][j-2] + dp[i-2][j-2] >= 0 &&
                dp[i][j] - dp[i-1][j] - dp[i-1][j-1] + dp[i-2][j-1] >= 0) {
                max_luckiness = fmax(max_luckiness, dp[i][j] - dp[i-2][j] - dp[i][j-2] + dp[i-2][j-2]);
            }

            // I shape
            if (dp[i][j] - dp[i-2][j] - dp[i][j-1] + dp[i-2][j-1] >= 0 &&
                dp[i][j] - dp[i-1][j] - dp[i-1][j-2] + dp[i-2][j-2] >= 0 &&
                dp[i][j] - dp[i-1][j] - dp[i-1][j-1] + dp[i-2][j-1] >= 0) {
                max_luckiness = fmax(max_luckiness, dp[i][j] - dp[i-2][j] - dp[i][j-2] + dp[i-2][j-2]);
            }
        }
    }

    printf("%d\n", max_luckiness);
    return 0;
}