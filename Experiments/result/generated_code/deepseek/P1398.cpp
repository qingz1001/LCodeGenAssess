#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150
#define MAXM 500

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][3];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = INT_MIN;
            }
        }
    }

    int ans = INT_MIN;

    // Calculate the maximum value for 'N'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && j > 0) {
                dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-1][0] + grid[i][j]);
            }
            if (i > 0) {
                dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][0] + grid[i][j]);
            }
            if (j > 0) {
                dp[i][j][0] = max(dp[i][j][0], dp[i][j-1][0] + grid[i][j]);
            }
            dp[i][j][0] = max(dp[i][j][0], grid[i][j]);
        }
    }

    // Calculate the maximum value for 'O'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && j > 0) {
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-1][1] + grid[i][j]);
            }
            if (i > 0) {
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1] + grid[i][j]);
            }
            if (j > 0) {
                dp[i][j][1] = max(dp[i][j][1], dp[i][j-1][1] + grid[i][j]);
            }
            dp[i][j][1] = max(dp[i][j][1], grid[i][j]);
        }
    }

    // Calculate the maximum value for 'I'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && j > 0) {
                dp[i][j][2] = max(dp[i][j][2], dp[i-1][j-1][2] + grid[i][j]);
            }
            if (i > 0) {
                dp[i][j][2] = max(dp[i][j][2], dp[i-1][j][2] + grid[i][j]);
            }
            if (j > 0) {
                dp[i][j][2] = max(dp[i][j][2], dp[i][j-1][2] + grid[i][j]);
            }
            dp[i][j][2] = max(dp[i][j][2], grid[i][j]);
        }
    }

    // Combine the results to find the maximum value
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = max(ans, dp[i][j][0] + dp[i][j][1] + dp[i][j][2] - 2 * grid[i][j]);
        }
    }

    printf("%d\n", ans);
    return 0;
}