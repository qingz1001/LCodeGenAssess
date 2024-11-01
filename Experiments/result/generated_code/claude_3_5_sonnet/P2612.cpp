#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 101
#define MOD 1000000007

long long dp[MAX_N][MAX_N * MAX_N];
long long fac[MAX_N];
long long inv[MAX_N];

long long quick_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = quick_pow(fac[i], MOD - 2);
    }
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    init();

    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= (n-1) * (n-2) / 2; j++) {
            for (int k = 0; k < i; k++) {
                int diff = j - k * (i - 1 - k);
                if (diff >= 0) {
                    dp[i][j] = (dp[i][j] + dp[i-1][diff]) % MOD;
                }
            }
        }
    }

    long long total = 0;
    for (int j = m; j <= (n-1) * (n-2) / 2; j++) {
        total = (total + dp[n][j]) % MOD;
    }

    long long result = total * inv[n] % MOD;
    double probability = (double)result / fac[n-1];

    printf("%.*f\n", k, probability);

    return 0;
}