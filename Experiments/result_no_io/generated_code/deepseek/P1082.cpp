#include <stdio.h>

// 扩展欧几里得算法
int exgcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, y, x);
    *y -= a / b * (*x);
    return gcd;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int x, y;
    exgcd(a, b, &x, &y);

    // 确保 x 是最小正整数解
    x = (x % b + b) % b;

    printf("%d\n", x);
    return 0;
}