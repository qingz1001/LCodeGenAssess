#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (m > n - 1) {
        printf("0\n");
        return 0;
    }

    long long dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    dp[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = ((dp[i - 1][j] * (i - 1)) % MOD + (j > 0 ? dp[i - 1][j - 1] : 0)) % MOD;
        }
    }

    printf("%lld\n", dp[n][m]);

    return 0;
}