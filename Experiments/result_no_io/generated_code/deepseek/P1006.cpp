#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int matrix[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int dp[m][n][m][n];
    memset(dp, 0, sizeof(dp));

    for (int x1 = 0; x1 < m; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            for (int x2 = 0; x2 < m; x2++) {
                for (int y2 = 0; y2 < n; y2++) {
                    if ((x1 == x2 && y1 == y2) || (x1 + y1 != x2 + y2)) {
                        continue;
                    }
                    int max_value = 0;
                    if (x1 > 0 && x2 > 0) {
                        max_value = MAX(max_value, dp[x1-1][y1][x2-1][y2]);
                    }
                    if (x1 > 0 && y2 > 0) {
                        max_value = MAX(max_value, dp[x1-1][y1][x2][y2-1]);
                    }
                    if (y1 > 0 && x2 > 0) {
                        max_value = MAX(max_value, dp[x1][y1-1][x2-1][y2]);
                    }
                    if (y1 > 0 && y2 > 0) {
                        max_value = MAX(max_value, dp[x1][y1-1][x2][y2-1]);
                    }
                    dp[x1][y1][x2][y2] = max_value + matrix[x1][y1] + matrix[x2][y2];
                }
            }
        }
    }

    printf("%d\n", dp[m-1][n-1][m-1][n-1]);

    return 0;
}