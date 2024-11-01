#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    // 计算不使用传送门的距离
    int direct_distance = abs(b - a);

    // 计算使用传送门的距离
    int teleport_distance1 = abs(x - a) + abs(y - b);
    int teleport_distance2 = abs(y - a) + abs(x - b);

    // 选择最小距离
    int min_distance = min(direct_distance, min(teleport_distance1, teleport_distance2));

    printf("%d\n", min_distance);

    return 0;
}