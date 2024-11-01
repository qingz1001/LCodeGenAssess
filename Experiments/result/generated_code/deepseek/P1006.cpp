#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 50

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int m, n;
    int matrix[MAX_M][MAX_N];
    int dp[MAX_M][MAX_N][MAX_M][MAX_N];

    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));

    for (int x1 = 0; x1 < m; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            for (int x2 = 0; x2 < m; x2++) {
                for (int y2 = 0; y2 < n; y2++) {
                    if (x1 == x2 && y1 == y2) continue; // Same cell, cannot use twice
                    int current_value = matrix[x1][y1] + matrix[x2][y2];
                    if (x1 > 0 && x2 > 0) dp[x1][y1][x2][y2] = max(dp[x1][y1][x2][y2], dp[x1-1][y1][x2-1][y2] + current_value);
                    if (x1 > 0 && y2 > 0) dp[x1][y1][x2][y2] = max(dp[x1][y1][x2][y2], dp[x1-1][y1][x2][y2-1] + current_value);
                    if (y1 > 0 && x2 > 0) dp[x1][y1][x2][y2] = max(dp[x1][y1][x2][y2], dp[x1][y1-1][x2-1][y2] + current_value);
                    if (y1 > 0 && y2 > 0) dp[x1][y1][x2][y2] = max(dp[x1][y1][x2][y2], dp[x1][y1-1][x2][y2-1] + current_value);
                }
            }
        }
    }

    printf("%d\n", dp[m-1][n-2][m-2][n-1] + matrix[m-1][n-1]);

    return 0;
}