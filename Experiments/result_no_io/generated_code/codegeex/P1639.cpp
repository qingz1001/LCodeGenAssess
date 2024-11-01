#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    // 计算直接运输的距离
    int direct_distance = abs(a - b);

    // 计算通过传送门的距离
    int teleport_distance = abs(a - x) + abs(y - b);

    // 比较两种方式，选择最小的距离
    int min_distance = (direct_distance < teleport_distance) ? direct_distance : teleport_distance;

    printf("%d\n", min_distance);

    return 0;
}