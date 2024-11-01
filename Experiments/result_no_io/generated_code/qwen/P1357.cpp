#include <stdio.h>

#define MOD 1000000007

long long power(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    if (k >= m - 1) {
        printf("0\n");
        return 0;
    }

    long long dp[m][2];
    for (int i = 0; i < m; i++) {
        dp[i][0] = 1;
        dp[i][1] = 0;
    }

    for (long long i = 2; i <= n; i++) {
        long long sum[2] = {0, 0};
        for (int j = 0; j < m; j++) {
            sum[(j + 1) % 2] = (sum[(j + 1) % 2] + dp[j][0]) % MOD;
        }
        for (int j = 0; j < m; j++) {
            dp[j][0] = (dp[j][0] * (sum[0] - dp[j][0] + MOD)) % MOD;
            dp[j][1] = (dp[j][1] * (sum[1] - dp[j][1])) % MOD;
        }
    }

    long long total = 0;
    for (int i = 0; i < m; i++) {
        total = (total + dp[i][0] + dp[i][1]) % MOD;
    }

    printf("%lld\n", total);
    return 0;
}