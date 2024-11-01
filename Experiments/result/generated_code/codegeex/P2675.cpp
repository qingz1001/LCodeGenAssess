#include <stdio.h>

#define MOD 10007

int main() {
    int n;
    scanf("%d", &n);

    // 计算阶乘和阶乘的逆元
    long long fact = 1, inv_fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact = (fact * i) % MOD;
    }
    // 计算阶乘的逆元，使用费马小定理
    for (int i = 1; i <= n; ++i) {
        inv_fact = (inv_fact * (n + 1 - i)) % MOD;
    }
    inv_fact = (inv_fact * (MOD + 1 - fact)) % MOD;

    // 计算结果
    long long result = (fact * inv_fact) % MOD;
    printf("%lld\n", result);

    return 0;
}