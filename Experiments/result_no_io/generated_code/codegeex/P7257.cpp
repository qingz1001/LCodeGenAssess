#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    // 翻转数字
    int reversed_a = (a % 10) * 100 + ((a / 10) % 10) * 10 + (a / 100);
    int reversed_b = (b % 10) * 100 + ((b / 10) % 10) * 10 + (b / 100);

    // 输出较大的翻转后的数字
    if (reversed_a > reversed_b) {
        printf("%d\n", reversed_a);
    } else {
        printf("%d\n", reversed_b);
    }

    return 0;
}