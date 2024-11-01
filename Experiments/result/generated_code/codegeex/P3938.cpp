#include <stdio.h>

// 计算斐波那契数列的第n项
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// 找到两个数的最大公约数
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == b) {
            printf("%d\n", a);
        } else {
            int fa = 1, fb = 1;
            while (fa != a && fb != b) {
                fa = fibonacci(fa);
                fb = fibonacci(fb);
            }
            if (fa == a || fb == b) {
                printf("%d\n", fa == a ? a : b);
            } else {
                int g = gcd(fa, fb);
                printf("%d\n", g);
            }
        }
    }
    return 0;
}