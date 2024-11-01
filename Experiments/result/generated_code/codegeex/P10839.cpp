#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);

    // 检查所有可能的运算组合
    if ((a + b + c == d) || (a + b * c == d) || (a * b + c == d) || (a * b * c == d) ||
        (a - b + c == d) || (a - b * c == d) || (a * b - c == d) || (a * b * c == d) ||
        (a + b - c == d) || (a + b * c == d) || (a - b + c == d) || (a - b * c == d)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}