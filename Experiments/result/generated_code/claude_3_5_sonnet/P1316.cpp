#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_N 21

long long pow_mod(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

long long inv(long long x) {
    return pow_mod(x, MOD - 2);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long dp[MAX_N][MAX_N] = {0};
    long long sum[MAX_N] = {0};

    for (int i = 1; i <= n; i++) {
        dp[i][i] = m;
        for (int j = i - 1; j >= 1; j--) {
            dp[i][j] = (dp[i][j+1] * m % MOD + m - dp[i-1][j]) % MOD;
        }
        for (int j = 1; j <= i; j++) {
            sum[i] = (sum[i] + dp[i][j]) % MOD;
        }
    }

    long long total = pow_mod(m, n);
    long long result = sum[n] * inv(total) % MOD;

    printf("%lld\n", result);

    return 0;
}