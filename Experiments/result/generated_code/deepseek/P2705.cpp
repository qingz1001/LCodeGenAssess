#include <stdio.h>

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int maxScore = 0;

    // 计算最大得分
    int redInRed = R;
    int blueInBlue = B;
    int redInBlue = 0;
    int blueInRed = 0;

    // 尝试将尽可能多的红色小球放在红色盒子里，蓝色小球放在蓝色盒子里
    if (C + D > 2 * E) {
        maxScore = R * C + B * D;
    } else {
        // 计算将红色小球放在蓝色盒子和蓝色小球放在红色盒子的最大得分
        int minRB = R < B ? R : B;
        maxScore = minRB * 2 * E + (R - minRB) * C + (B - minRB) * D;
    }

    printf("%d\n", maxScore);

    return 0;
}