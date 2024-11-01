#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 666623333

// 快速幂函数，用于计算 a^b % mod
long long mod_pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);

    int l[2005], r[2005];
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    long long fact[2005], inv_fact[2005];
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        inv_fact[i] = mod_pow(fact[i], MOD - 2, MOD);
    }

    long long ans = 0;
    for (int i = 1; i <= x; i++) {
        long long sum = 0;
        for (int j = 0; j < q; j++) {
            int count = 0;
            for (int k = l[j]; k <= r[j]; k++) {
                if (k % i == 0) {
                    count++;
                }
            }
            sum = (sum + count) % MOD;
        }
        long long p = mod_pow(x, sum, MOD);
        long long term = (p - 1 + MOD) % MOD;
        term = (term * inv_fact[sum]) % MOD;
        ans = (ans + term) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}