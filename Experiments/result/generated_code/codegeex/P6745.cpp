#include <stdio.h>

int main() {
    long long k, x;
    scanf("%lld %lld", &k, &x);

    // 计算 10^k
    long long power_of_10 = 1;
    for (long long i = 0; i < k; i++) {
        power_of_10 *= 10;
    }

    // 计算 10^k + x
    long long result = power_of_10 + x;

    // 输出结果
    printf("%lld\n", result);

    return 0;
}