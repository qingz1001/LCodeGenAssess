#include <stdio.h>
#include <stdint.h>

#define MOD 998244353

// 计算组合数 C(n, k) % MOD
uint64_t comb(uint64_t n, uint64_t k, uint64_t mod) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k == 1 || k == n - 1) return n % mod;

    uint64_t result = 1;
    for (uint64_t i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i % mod;
    }
    return result;
}

// 快速幂
uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    uint64_t N, M, S, L;
    scanf("%llu %llu %llu %llu", &N, &M, &S, &L);

    for (uint64_t i = 0; i < S; i++) {
        uint64_t n, m, k;
        scanf("%llu %llu %llu", &n, &m, &k);

        uint64_t total_combinations = comb(n, k, MOD);
        uint64_t expected_failure = 0;

        for (uint64_t x = 0; x <= k && x <= m; x++) {
            uint64_t combinations = comb(m, x, MOD) * comb(n - m, k - x, MOD) % MOD;
            uint64_t failure_degree = pow_mod(x, L, MOD);
            expected_failure = (expected_failure + combinations * failure_degree % MOD) % MOD;
        }

        expected_failure = expected_failure * pow_mod(total_combinations, MOD - 2, MOD) % MOD;
        printf("%llu\n", expected_failure);
    }

    return 0;
}