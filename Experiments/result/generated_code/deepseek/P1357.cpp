#include <stdio.h>
#include <stdint.h>

#define MOD 1000000007

int64_t mod_exp(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int64_t solve(int64_t n, int64_t m, int64_t k) {
    if (k == 0) {
        return mod_exp(2, n, MOD);
    }

    int64_t total_ways = mod_exp(2, n, MOD);
    int64_t invalid_ways = 0;

    for (int64_t i = 1; i <= k; ++i) {
        invalid_ways = (invalid_ways + mod_exp(i, n, MOD) * mod_exp(2, n - i, MOD)) % MOD;
    }

    return (total_ways - invalid_ways + MOD) % MOD;
}

int main() {
    int64_t n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    printf("%lld\n", solve(n, m, k));
    return 0;
}