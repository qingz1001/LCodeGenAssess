#include <stdio.h>

// 计算最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    // 找出最大值和最小值
    int max = a;
    int min = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }

    // 计算最大公约数
    int d = gcd(max, min);

    // 输出约分后的分数
    printf("%d/%d\n", min / d, max / d);

    return 0;
}