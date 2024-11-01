#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 计算两个宝箱的绝对值之和
    int sum = abs(a) + abs(b);

    // 输出结果
    printf("%d\n", sum);

    return 0;
}