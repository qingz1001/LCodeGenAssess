#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 计算两个宝箱的绝对距离
    int distance = abs(a) + abs(b);

    // 输出最少移动次数
    printf("%d\n", distance);

    return 0;
}