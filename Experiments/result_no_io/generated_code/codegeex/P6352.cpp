#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    // 对输入的三个数进行排序
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    if (a > c) {
        int t = a;
        a = c;
        c = t;
    }
    if (b > c) {
        int t = b;
        b = c;
        c = t;
    }

    // 根据排序后的三个数，确定第四个数
    int d;
    if (b - a == c - b) {
        d = a - (b - a) + 4 * (b - a);
    } else {
        d = a + 2 * (b - a);
    }

    printf("%d\n", d);
    return 0;
}