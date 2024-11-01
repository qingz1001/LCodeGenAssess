#include <stdio.h>
#define MOD 1000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= a[j - 1]; k++) {
                if (i >= k) {
                    dp[i][j] = (dp[i][j] + dp[i - k][j - 1]) % MOD;
                }
            }
        }
    }

    printf("%lld\n", dp[m][n]);

    return 0;
}