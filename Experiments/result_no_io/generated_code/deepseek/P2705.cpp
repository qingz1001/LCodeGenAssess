#include <stdio.h>

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int maxScore = 0;

    // 计算最大得分
    int redInRed = R < R ? R : R;
    int blueInBlue = B < B ? B : B;
    int redInBlue = R - redInRed;
    int blueInRed = B - blueInBlue;

    maxScore = redInRed * C + blueInBlue * D + redInBlue * E + blueInRed * E;

    printf("%d\n", maxScore);

    return 0;
}