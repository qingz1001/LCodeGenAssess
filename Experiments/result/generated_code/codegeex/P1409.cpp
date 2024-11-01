#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double dp[1001][1001] = {0};
    dp[n][n] = 1.0;

    for (int i = n - 1; i >= m; i--) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = (dp[i][j + 1] + dp[i + 1][j] + dp[i + 1][j + 1]) / 6.0;
        }
    }

    printf("%.9lf\n", dp[m][m]);
    return 0;
}