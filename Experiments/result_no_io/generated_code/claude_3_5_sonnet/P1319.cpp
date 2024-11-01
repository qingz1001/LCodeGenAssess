#include <stdio.h>

#define MAX_N 200

int main() {
    int N;
    int compressed[MAX_N * MAX_N + 1];
    char matrix[MAX_N][MAX_N];
    int count = 0;
    int index = 0;
    char current_char = '0';

    // 读取压缩码
    scanf("%d", &N);
    int i = 0;
    while (scanf("%d", &compressed[i]) == 1) {
        i++;
    }

    // 解压缩并填充矩阵
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (count == 0) {
                count = compressed[index++];
                current_char = (current_char == '0') ? '1' : '0';
            }
            matrix[row][col] = current_char;
            count--;
        }
    }

    // 输出矩阵
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%c", matrix[row][col]);
        }
        printf("\n");
    }

    return 0;
}