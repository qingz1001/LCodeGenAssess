#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (n <= k) {
        printf("0\n");
        return 0;
    }

    int dp[n + 1][k + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        dp[i][1] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j - 1];
            if (i >= j * 2) {
                dp[i][j] += dp[i - j][j];
            }
        }
    }

    printf("%d\n", dp[n][k]);

    return 0;
}