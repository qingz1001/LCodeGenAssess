#include <stdio.h>
#include <math.h>

int main() {
    long long k, x;
    scanf("%lld%lld", &k, &x);

    // 计算 10^k
    long long power_of_10 = pow(10, k);

    // 计算 10^k + x
    long long result = power_of_10 + x;

    // 输出结果
    printf("%lld\n", result);

    return 0;
}