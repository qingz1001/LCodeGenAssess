#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (m > n * (n - 1) / 2) {
        printf("0\n");
        return 0;
    }

    long long dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (j > 0) {
                dp[i][j] = (dp[i][j] + (long long)i * (i - 1) / 2 * dp[i - 2][j - 1]) % MOD;
            }
        }
    }

    printf("%lld\n", dp[n][m]);

    return 0;
}