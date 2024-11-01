#include <stdio.h>

int main() {
    long long a1, a2, n;
    scanf("%lld %lld %lld", &a1, &a2, &n);

    // 计算公差
    long long d = a2 - a1;

    // 计算首项和末项
    long long first_term = a1;
    long long last_term = a1 + (n - 1) * d;

    // 计算等差数列的和
    long long sum = (n * (first_term + last_term)) / 2;

    // 输出结果
    printf("%lld\n", sum);

    return 0;
}