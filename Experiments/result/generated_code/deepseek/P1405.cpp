#include <stdio.h>
#include <stdint.h>

#define MOD 10007

// 快速幂函数，计算 (base^exp) % mod
int64_t fast_pow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int64_t a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    int64_t result = a[n-1];
    for (int i = n-2; i >= 0; i--) {
        result = fast_pow(a[i], result, MOD);
    }

    printf("%lld\n", result);
    return 0;
}