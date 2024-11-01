#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXM 1300

int dp[MAXN][MAXM];
int values[MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &values[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i-1][j] != -1) {
                for (int k = 0; k <= i; ++k) {
                    if (j + k <= m) {
                        dp[i][j+k] = dp[i][j+k] == -1 ? dp[i-1][j] + values[i][k] : fmax(dp[i][j+k], dp[i-1][j] + values[i][k]);
                    }
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j <= m; ++j) {
        result = fmax(result, dp[n][j]);
    }

    printf("%d\n", result);

    return 0;
}