#include <stdio.h>

// 快速幂函数，用于计算 (base^exp) % mod
long long fast_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // 如果当前指数是奇数
            result = (result * base) % mod; // 更新结果
        }
        base = (base * base) % mod; // 基数平方
        exp /= 2; // 指数减半
    }
    return result;
}

int main() {
    long long a, b, p;
    // 读取输入的三个整数
    scanf("%lld %lld %lld", &a, &b, &p);
    // 计算并输出结果
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, fast_pow(a, b, p));
    return 0;
}