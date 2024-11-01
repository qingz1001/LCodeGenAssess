#include <stdio.h>
#include <stdbool.h>

bool isSafe(int hunter_x, int hunter_y, int rabbit_x, int rabbit_y) {
    // 计算两个点之间的横纵坐标差值
    int dx = rabbit_x - hunter_x;
    int dy = rabbit_y - hunter_y;

    // 如果横纵坐标差值相等，则两点在同一直线上
    if (dx == 0 || dy == 0) {
        return false;
    }

    // 计算横纵坐标差值的最大公约数
    int gcd = dx;
    int temp = dy;
    while (temp != 0) {
        int t = temp;
        temp = gcd % temp;
        gcd = t;
    }

    // 如果最大公约数等于1，则两点之间没有其他点
    return gcd != 1;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int hunter_x, hunter_y, rabbit_x, rabbit_y;
        scanf("%d %d", &hunter_x, &hunter_y);
        scanf("%d %d", &rabbit_x, &rabbit_y);

        if (isSafe(hunter_x, hunter_y, rabbit_x, rabbit_y)) {
            printf("no\n");
        } else {
            printf("yes\n");
        }
    }

    return 0;
}