#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inv(long long x, long long mod) {
    return mod_pow(x, mod - 2, mod);
}

long long comb(long long n, long long k, long long mod) {
    if (k > n) return 0;
    long long numerator = 1, denominator = 1;
    for (long long i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * mod_inv(denominator, mod)) % mod;
}

int main() {
    long long N, M, S, L;
    scanf("%lld %lld %lld %lld", &N, &M, &S, &L);

    for (int i = 0; i < S; i++) {
        long long n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);

        long long total_ways = comb(n, k, MOD);
        long long expected_failure = 0;

        for (long long x = 0; x <= k && x <= m; x++) {
            long long ways_to_choose_x_flat = comb(m, x, MOD);
            long long ways_to_choose_k_minus_x_normal = comb(n - m, k - x, MOD);
            long long probability = (ways_to_choose_x_flat * ways_to_choose_k_minus_x_normal) % MOD;
            probability = (probability * mod_inv(total_ways, MOD)) % MOD;
            long long failure_value = mod_pow(x, L, MOD);
            expected_failure = (expected_failure + (probability * failure_value) % MOD) % MOD;
        }

        printf("%lld\n", expected_failure);
    }

    return 0;
}