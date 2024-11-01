#include <stdio.h>
#include <stdint.h>

#define MOD 998244353

// 计算欧拉函数 φ(n)
uint64_t euler_phi(uint64_t n) {
    uint64_t result = n;
    for (uint64_t p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// 计算 (sum_{i=1}^n sum_{j=1}^m φ(ij)) % MOD
uint64_t solve(uint64_t n, uint64_t m) {
    uint64_t sum = 0;
    for (uint64_t i = 1; i <= n; ++i) {
        for (uint64_t j = 1; j <= m; ++j) {
            sum = (sum + euler_phi(i * j)) % MOD;
        }
    }
    return sum;
}

int main() {
    uint64_t T;
    scanf("%llu", &T);
    while (T--) {
        uint64_t n, m;
        scanf("%llu %llu", &n, &m);
        printf("%llu\n", solve(n, m));
    }
    return 0;
}