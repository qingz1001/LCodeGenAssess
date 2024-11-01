#include <stdio.h>

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    int direct_distance = abs(a - b); // 直接运输的距离
    int teleport_distance = abs(a - x) + abs(y - b); // 使用传送门运输的距离

    int min_distance = direct_distance; // 初始化最小距离为直接运输的距离

    // 比较两种运输方式，选择最小距离
    if (teleport_distance < min_distance) {
        min_distance = teleport_distance;
    }

    printf("%d\n", min_distance);

    return 0;
}