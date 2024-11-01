#include <stdio.h>

#define MOD 1000000007

int main() {
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    long long dp[m + 1][k + 1];
    for (long long i = 0; i <= m; i++) {
        for (long long j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    dp[1][0] = 1;

    for (long long i = 2; i <= n; i++) {
        long long new_dp[m + 1][k + 1];
        for (long long j = 0; j <= m; j++) {
            for (long long l = 0; l <= k; l++) {
                new_dp[j][l] = 0;
            }
        }

        for (long long j = 1; j <= m; j++) {
            for (long long l = 0; l <= k; l++) {
                if (j == 1) {
                    new_dp[j][(l + 1) % m] += dp[j - 1][l];
                    new_dp[j][(l + 1) % m] %= MOD;
                } else {
                    new_dp[j][(l + 1) % m] += dp[j - 1][l];
                    new_dp[j][(l + 1) % m] %= MOD;
                    new_dp[j][l] += dp[j - 1][l];
                    new_dp[j][l] %= MOD;
                }
            }
        }

        for (long long j = 0; j <= m; j++) {
            for (long long l = 0; l <= k; l++) {
                dp[j][l] = new_dp[j][l];
            }
        }
    }

    long long result = 0;
    for (long long j = 0; j <= k; j++) {
        result += dp[m][j];
        result %= MOD;
    }

    printf("%lld\n", result);

    return 0;
}