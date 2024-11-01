#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define MAXM 1275  // n * (n + 1) / 2

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int bricks[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &bricks[i][j]);
        }
    }

    int dp[MAXN][MAXM];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = j; k <= m; k++) {
                if (j > 0) {
                    dp[i][k] = max(dp[i][k], dp[i - 1][k - j] + bricks[i - 1][j - 1]);
                } else {
                    dp[i][k] = max(dp[i][k], dp[i - 1][k]);
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= m; i++) {
        result = max(result, dp[n][i]);
    }

    printf("%d\n", result);

    return 0;
}