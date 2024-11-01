#include <stdio.h>

// 求最大公约数
long gcd(long a, long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 扩展欧几里得算法
void extended_gcd(long a, long b, long *x, long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    long x1, y1;
    extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}

int main() {
    long a, b;
    scanf("%ld %ld", &a, &b);

    long x, y;
    extended_gcd(a, b, &x, &y);

    // 调整x为正整数解
    x = (x % b + b) % b;

    printf("%ld\n", x);
    return 0;
}