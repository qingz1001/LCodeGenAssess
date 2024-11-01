#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_N 21

long long pow_mod(long long base, int exp, int mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long inv(long long x) {
    return pow_mod(x, MOD - 2, MOD);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long dp[MAX_N][MAX_N] = {0};
    long long sum[MAX_N] = {0};
    long long inv_m = inv(m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1) {
                dp[i][j] = m;
            } else {
                dp[i][j] = (dp[i-1][j-1] * (m - 1) % MOD + dp[i-1][j] * j % MOD) % MOD;
            }
            sum[i] = (sum[i] + dp[i][j]) % MOD;
        }
    }

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + sum[i] * inv_m % MOD) % MOD;
    }

    printf("%lld\n", result);

    return 0;
}