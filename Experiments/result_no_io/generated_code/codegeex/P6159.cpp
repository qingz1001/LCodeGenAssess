#include <stdio.h>

int main() {
    long long n, p, k;
    scanf("%lld%lld%lld", &n, &p, &k);

    // 计算光经过 k 次反射后的位置
    // 每次反射，光会沿着圆周行进 n 个点
    long long t = (p + k * n) % n;

    // 输出最终位置
    printf("%lld\n", t);

    return 0;
}