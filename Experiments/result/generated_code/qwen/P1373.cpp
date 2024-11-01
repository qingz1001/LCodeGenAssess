#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    long long **dp = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++) {
        dp[i] = (long long *)malloc(m * sizeof(long long));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 0;
                if (i > 0) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
                }
                if (j > 0) {
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
                }
            }
        }
    }

    printf("%lld\n", dp[n - 1][m - 1]);

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}