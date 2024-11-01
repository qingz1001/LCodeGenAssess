#include <stdio.h>
#include <stdint.h>

#define MOD 998244353

// 快速幂函数
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

// 组合数计算函数
int64_t comb(int64_t n, int64_t k, int64_t mod) {
    int64_t numerator = 1, denominator = 1;
    for (int64_t i = 1; i <= k; ++i) {
        numerator = (numerator * (n - i + 1)) % mod;
        denominator = (denominator * i) % mod;
    }
    return (numerator * mod_exp(denominator, mod - 2, mod)) % mod;
}

// 计算权值为 i 的序列数量
int64_t count_sequences(int64_t n, int64_t i) {
    int64_t total_sequences = mod_exp(3, n, MOD);
    int64_t valid_sequences = 0;
    for (int64_t j = 0; j <= i; ++j) {
        valid_sequences = (valid_sequences + comb(n - 2 * j, n - 2 * j - 1, MOD)) % MOD;
    }
    return (total_sequences - valid_sequences + MOD) % MOD;
}

int main() {
    int64_t n, k;
    scanf("%" PRId64 " %" PRId64, &n, &k);

    for (int64_t i = 0; i <= k; ++i) {
        printf("%" PRId64 " ", count_sequences(n, i));
    }
    printf("\n");

    return 0;
}