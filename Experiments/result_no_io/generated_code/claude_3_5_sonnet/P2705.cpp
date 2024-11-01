#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int max_score;

    if (C + D > 2 * E) {
        // 如果C+D > 2E，那么最优策略是尽可能多地将红球放入红盒、蓝球放入蓝盒
        max_score = R * C + B * D;
    } else {
        // 否则，最优策略是尽可能多地进行交叉放置
        int cross = min(R, B);
        max_score = cross * 2 * E + (R > B ? (R - B) * C : (B - R) * D);
    }

    printf("%d\n", max_score);

    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}