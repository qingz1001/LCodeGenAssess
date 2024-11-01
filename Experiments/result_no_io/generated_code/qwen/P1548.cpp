#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int squares = 0;
    int rectangles = 0;

    // 计算正方形的数量
    for (int size = 1; size <= N && size <= M; size++) {
        squares += (N - size + 1) * (M - size + 1);
    }

    // 计算长方形的数量
    for (int width = 1; width <= M; width++) {
        for (int height = 1; height <= N; height++) {
            if (width != height) {
                rectangles += (M - width + 1) * (N - height + 1);
            }
        }
    }

    printf("%d %d\n", squares, rectangles);

    return 0;
}