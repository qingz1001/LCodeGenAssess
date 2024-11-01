#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 计算 a 和 b 的最大公约数
    int gcd = a % b;
    while (gcd != 0) {
        a = b;
        b = gcd;
        gcd = a % b;
    }

    // 输出最小体积
    printf("%d\n", b);

    // 计算倒酒次数
    int Pa = b, Pb = a / b;
    printf("%d %d\n", Pa, Pb);

    return 0;
}