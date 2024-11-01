#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int abs(int x) {
    return (x < 0) ? -x : x;
}

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    // 确保a <= b
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // 计算直接运输的距离
    int direct_distance = abs(b - a);

    // 计算使用传送门的距离
    int teleport_distance1 = abs(a - x) + abs(b - y);
    int teleport_distance2 = abs(a - y) + abs(b - x);

    // 找出最小距离
    int min_distance = min(direct_distance, min(teleport_distance1, teleport_distance2));

    printf("%d\n", min_distance);

    return 0;
}