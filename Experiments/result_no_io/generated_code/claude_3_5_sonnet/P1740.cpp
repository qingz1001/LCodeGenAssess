#include <stdio.h>
#include <string.h>

#define MAX_N 888

char grid[MAX_N * 2][MAX_N * 2];
int output[MAX_N * 2 + 1][MAX_N * 2];

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 消耗换行符

    // 读取输入
    for (int i = 0; i < 2 * n; i++) {
        fgets(grid[i], sizeof(grid[i]), stdin);
    }

    // 处理输入并生成输出
    for (int i = 0; i < n; i++) {
        int start = n - i - 1;
        for (int j = 0; j < 2 * i + 1; j++) {
            if (j % 2 == 0) {
                output[i][start + j] = (grid[i][start + j] == '/') ? 1 : 0;
                output[2 * n - i][start + j] = (grid[2 * n - i - 1][start + j] == '\\') ? 1 : 0;
            } else {
                output[i + 1][start + j] = (grid[i][start + j] == '\\') ? 1 : 0;
                output[2 * n - i - 1][start + j] = (grid[2 * n - i - 1][start + j] == '/') ? 1 : 0;
            }
        }
    }

    // 输出结果
    printf("%d\n", n);
    for (int i = 0; i <= 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            printf("%d", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}