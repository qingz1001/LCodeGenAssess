#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    // 计算两个宝箱到原点的绝对距离之和
    int total_distance = abs(a) + abs(b);

    printf("%d\n", total_distance);
    return 0;
}