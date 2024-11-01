#include <stdio.h>

// 快速幂算法
long long fast_pow(long long base, long long exp, long long mod) {
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

int main() {
    long long a, b, p;
    scanf("%lld %lld %lld", &a, &b, &p);

    long long result = fast_pow(a, b, p);

    printf("%lld^%lld mod %lld=%lld\n", a, b, p, result);

    return 0;
}