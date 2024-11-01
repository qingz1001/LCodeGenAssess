#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 定义常量
    const int MOD = 10007;

    // 阶乘数组
    long long factorial[1000001] = {1};

    // 计算阶乘
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }

    // 计算组合数 C(n, k) = n! / (k! * (n - k)!)
    long long combination = 0;
    for (int k = 0; k <= n / 2; k++) {
        long long numerator = factorial[n - 2 * k];
        long long denominator = (factorial[k] * factorial[2 * k]) % MOD;
        combination = (combination + (numerator * factorial[2 * k + 1]) % MOD * (MOD + 1 - denominator) % MOD) % MOD;
    }

    printf("%lld\n", combination);
    return 0;
}