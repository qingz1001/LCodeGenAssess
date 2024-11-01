#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int square_count = 0;
    int rectangle_count = 0;

    // 计算正方形的个数
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i == j) {
                square_count += i * j;
            } else {
                square_count += 2 * i * j;
            }
        }
    }

    // 计算长方形的个数
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i != j) {
                rectangle_count += (i * M + j * N - 2 * i * j);
            }
        }
    }

    printf("%d %d\n", square_count, rectangle_count);

    return 0;
}