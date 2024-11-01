#include <stdio.h>

// 计算斐波那契数列的第n项
long long fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int m;
    scanf("%d", &m);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == b) {
            printf("%d\n", a);
        } else {
            long long fa = fibonacci(a);
            long long fb = fibonacci(b);
            if (fa == fb) {
                printf("%lld\n", fa);
            } else {
                printf("%lld\n", fibonacci(a > b ? a - 1 : b - 1));
            }
        }
    }
    return 0;
}