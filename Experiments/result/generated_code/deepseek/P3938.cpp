#include <stdio.h>
#include <stdlib.h>

// 计算斐波那契数列的第n项
unsigned long long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// 计算兔子的最近公共祖先
int lca(int a, int b) {
    while (a != b) {
        if (a > b) {
            a /= 2;
        } else {
            b /= 2;
        }
    }
    return a;
}

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}