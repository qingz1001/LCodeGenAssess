#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    long long squares = 0, rectangles = 0;

    // 计算正方形数量
    for (int i = 1; i <= N && i <= M; i++) {
        squares += (N - i + 1) * (M - i + 1);
    }

    // 计算长方形数量（不包括正方形）
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i != j) {
                rectangles += (N - i + 1) * (M - j + 1);
            }
        }
    }

    printf("%lld %lld\n", squares, rectangles);

    return 0;
}