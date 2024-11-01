#include <stdio.h>

#define MOD 9901

long long dp[205][105];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    dp[1][1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i == 1) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 0;
                for (int l = 0; l < i; l++) {
                    dp[i][j] = (dp[i][j] + dp[l][j - 1] * dp[i - 1 - l][j - 1] % MOD) % MOD;
                }
            }
        }
    }

    printf("%lld\n", dp[n][k]);
    return 0;
}