#include <stdio.h>

// 求最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
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

    // 约分并输出结果
    int divisor = gcd(max, min);
    printf("%d/%d\n", min / divisor, max / divisor);

    return 0;
}