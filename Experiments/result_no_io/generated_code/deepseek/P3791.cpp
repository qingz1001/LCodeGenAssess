#include <stdio.h>
#include <stdint.h>

#define MOD 998244353

// 计算x的约数个数
int64_t divisor_count(int64_t x) {
    if (x == 0) return 0;
    int64_t count = 0;
    for (int64_t i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            count++;
            if (i != x / i) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int64_t n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);

    int64_t result = 0;
    for (int64_t i = 0; i <= n; i++) {
        for (int64_t j = 0; j <= m; j++) {
            int64_t value = i ^ j ^ x;
            result = (result + divisor_count(value)) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}