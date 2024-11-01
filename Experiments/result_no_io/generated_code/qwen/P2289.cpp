#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    if (m * n % 2 != 0) {
        printf("0\n");
        return 0;
    }

    long long dp[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    printf("%lld\n", dp[m - 1][n - 1]);

    return 0;
}