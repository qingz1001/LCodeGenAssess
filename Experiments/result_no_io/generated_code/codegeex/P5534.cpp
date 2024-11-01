#include <stdio.h>

int main() {
    long long a1, a2, n, d, sum = 0;
    scanf("%lld %lld %lld", &a1, &a2, &n);

    // 计算公差
    d = a2 - a1;

    // 计算等差数列的和
    sum = (n * (2 * a1 + (n - 1) * d)) / 2;

    // 输出结果
    printf("%lld\n", sum);

    return 0;
}