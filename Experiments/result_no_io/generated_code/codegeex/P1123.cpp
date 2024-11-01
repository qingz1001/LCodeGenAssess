#include <stdio.h>

int main() {
    int T, N, M, i, j, k, max, sum;
    int matrix[6][6];

    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        // 遍历所有可能的取数方案
        max = 0;
        for (i = 0; i < (1 << (N * M)); i++) {
            sum = 0;
            for (j = 0, k = 0; j < N * M; j++, k++) {
                if (i & (1 << j)) {
                    sum += matrix[k / M][k % M];
                    // 检查相邻的8个格子是否有数字
                    if (k - 1 >= 0 && (i & (1 << (k - 1)))) sum = -1;
                    if (k + 1 < N * M && (i & (1 << (k + 1)))) sum = -1;
                    if (k - M >= 0 && (i & (1 << (k - M)))) sum = -1;
                    if (k + M < N * M && (i & (1 << (k + M)))) sum = -1;
                    if (k - M - 1 >= 0 && (i & (1 << (k - M - 1)))) sum = -1;
                    if (k - M + 1 >= 0 && (i & (1 << (k - M + 1)))) sum = -1;
                    if (k + M - 1 < N * M && (i & (1 << (k + M - 1)))) sum = -1;
                    if (k + M + 1 < N * M && (i & (1 << (k + M + 1)))) sum = -1;
                }
            }
            if (sum > max) max = sum;
        }
        printf("%d\n", max);
    }
    return 0;
}