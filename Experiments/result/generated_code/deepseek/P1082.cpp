#include <stdio.h>

// 扩展欧几里得算法
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int x, y;
    extended_gcd(a, b, &x, &y);

    // 确保 x 是正数
    if (x < 0) {
        x += b;
    }

    printf("%d\n", x);
    return 0;
}