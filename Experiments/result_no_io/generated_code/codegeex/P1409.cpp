#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    double dp[1001][1001] = {0.0};
    dp[1][1] = 1.0;

    for (int i = 2; i <= n; i++) {
        dp[i][1] = dp[i-1][1] * 0.5 + dp[i-1][i] * 0.5;
        for (int j = 2; j < i; j++) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] * 2.0 + dp[i-1][i]) / 3.0;
        }
        dp[i][i] = dp[i-1][i] * 0.5 + dp[i-1][i-1] * 0.5;
    }

    printf("%.9f\n", dp[n][m]);
    return 0;
}