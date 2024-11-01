#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 找到 a 和 b 的最大公约数 g
    int g = a % b;
    while (g != 0) {
        a = b;
        b = g;
        g = a % b;
    }

    // 输出最小体积 c
    printf("%d\n", b);

    // 输出倒酒次数 Pa 和 Pb
    int Pa = a / b;
    int Pb = 1;
    printf("%d %d\n", Pa, Pb);

    return 0;
}