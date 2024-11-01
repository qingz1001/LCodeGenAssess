#include <stdio.h>
#include <stdint.h>

#define MOD 1000000007

// 快速幂函数
int64_t fast_pow(int64_t base, int64_t exp, int64_t mod) {
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
    if (n % 2 == 0) {
        return (k * fast_pow(k, n - 1, p)) % p;
    } else {
        return (k * fast_pow(k, n / 2, p) * (k + 1)) % p;
    }
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