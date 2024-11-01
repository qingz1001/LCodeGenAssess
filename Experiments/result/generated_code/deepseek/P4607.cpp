#include <stdio.h>
#include <stdint.h>

// 快速幂函数，计算 (base^exp) % mod
int64_t mod_pow(int64_t base, int64_t exp, int64_t mod) {
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

// 计算讨厌的字符串数量
int64_t count_hated_strings(int64_t n, int64_t k, int64_t p) {
    if (n == 1) return k % p;
    if (n == 2) return (k * k) % p;

    int64_t half_n = n / 2;
    int64_t half_k = mod_pow(k, half_n, p);
    int64_t result = (half_k * half_k) % p;

    if (n % 2 == 1) {
        result = (result * k) % p;
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int64_t n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);
        printf("%lld\n", count_hated_strings(n, k, p));
    }
    return 0;
}