#include <stdio.h>

int main() {
    int a, b, rev_a, rev_b;
    scanf("%d %d", &a, &b);

    // 翻转 a
    rev_a = (a % 10) * 100 + ((a / 10) % 10) * 10 + (a / 100);
    // 翻转 b
    rev_b = (b % 10) * 100 + ((b / 10) % 10) * 10 + (b / 100);

    // 比较翻转后的数，输出较大者
    if (rev_a > rev_b) {
        printf("%d\n", rev_a);
    } else {
        printf("%d\n", rev_b);
    }

    return 0;
}