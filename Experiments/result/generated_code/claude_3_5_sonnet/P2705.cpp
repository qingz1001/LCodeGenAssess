#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int score;
    if (C + D >= 2 * E) {
        // 如果C+D >= 2E，则最优策略是尽可能多地将红球放入红盒，蓝球放入蓝盒
        score = R * C + B * D;
    } else {
        // 否则，最优策略是尽可能多地进行交叉放置
        int cross = R < B ? R : B;
        int remain = R + B - 2 * cross;
        score = 2 * cross * E + remain * max(C, D);
    }

    printf("%d\n", score);

    return 0;
}