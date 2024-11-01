#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    if (N % 2 != 0) {
        printf("This is a dangerous situation!\n");
        return 0;
    }

    int *x = (int *)malloc(N * sizeof(int));
    int *y = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    // 检查所有点是否满足对称条件
    for (int i = 0; i < N / 2; i++) {
        if (x[i] != x[N - 1 - i] || y[i] != y[N - 1 - i]) {
            printf("This is a dangerous situation!\n");
            free(x);
            free(y);
            return 0;
        }
    }

    // 计算对称中心的坐标
    double centerX = 0.0, centerY = 0.0;
    for (int i = 0; i < N; i++) {
        centerX += x[i];
        centerY += y[i];
    }
    centerX /= N;
    centerY /= N;

    printf("V.I.P. should stay at (%.1f,%.1f).\n", centerX, centerY);

    free(x);
    free(y);
    return 0;
}