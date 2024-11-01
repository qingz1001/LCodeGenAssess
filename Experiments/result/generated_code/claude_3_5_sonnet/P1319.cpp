#include <stdio.h>

#define MAX_N 200

int main() {
    int N, matrix[MAX_N][MAX_N] = {0};
    int code[MAX_N * MAX_N] = {0};
    int code_len = 0;

    // 读取压缩码
    while (scanf("%d", &code[code_len]) != EOF) {
        code_len++;
    }

    N = code[0];
    int row = 0, col = 0, current = 0;

    // 解压缩
    for (int i = 1; i < code_len; i++) {
        int count = code[i];
        for (int j = 0; j < count; j++) {
            matrix[row][col] = current;
            col++;
            if (col == N) {
                col = 0;
                row++;
            }
        }
        current = 1 - current;  // 切换0和1
    }

    // 输出点阵图案
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}