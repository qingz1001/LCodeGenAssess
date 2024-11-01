#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define INF -1e9

int dp[MAXN][MAXN][2];
int a[MAXN][MAXN];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    dp[1][1][0] = a[1][1];

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dp[i-1][j][0] != INF) {
                dp[i][j][0] = dp[i-1][j][0] + a[i][j];
            }
            if (dp[i][j-1][0] != INF) {
                dp[i][j][0] = dp[i][j-1][0] + a[i][j];
            }
            if (dp[i-1][j][1] != INF) {
                dp[i][j][1] = dp[i-1][j][1] + a[i][j];
            }
            if (dp[i][j-1][1] != INF) {
                dp[i][j][1] = dp[i][j-1][1] + a[i][j];
            }
        }
    }

    printf("%d\n", dp[m][n][0] + dp[m][n][1] - a[m][n]);

    return 0;
}