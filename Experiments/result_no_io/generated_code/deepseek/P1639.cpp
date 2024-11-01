#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    // 计算直接从a到b的距离
    int direct_distance = abs(a - b);

    // 计算使用传送门的距离
    int teleport_distance1 = abs(a - x) + abs(b - y);
    int teleport_distance2 = abs(a - y) + abs(b - x);

    // 取最小值
    int min_distance = direct_distance;
    if (teleport_distance1 < min_distance) {
        min_distance = teleport_distance1;
    }
    if (teleport_distance2 < min_distance) {
        min_distance = teleport_distance2;
    }

    printf("%d\n", min_distance);
    return 0;
}