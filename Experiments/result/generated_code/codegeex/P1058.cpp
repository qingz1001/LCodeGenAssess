#include <stdio.h>
#include <string.h>

#define MAXN 100

char map[MAXN][MAXN * 4]; // 用于存储最终输出结果的二维字符数组
int stack[MAXN][MAXN];    // 用于存储每个格子上摞的积木数量的二维数组

int main() {
    int m, n, i, j, k, l, max_height = 0, width, height;
    
    // 读取矩阵的行数和列数
    scanf("%d %d", &m, &n);
    
    // 读取每个格子上摞的积木数量，并计算最高的高度
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &stack[i][j]);
            if (stack[i][j] > max_height) {
                max_height = stack[i][j];
            }
        }
    }
    
    // 计算输出结果矩阵的宽度
    width = n * 4 + (n - 1) * 2;
    
    // 初始化输出结果矩阵
    memset(map, '.', sizeof(map));
    
    // 构建立体图
    for (k = max_height - 1; k >= 0; k--) {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (stack[i][j] > k) {
                    // 构建积木的各个部分
                    map[i + k][j * 4 + j * 2] = '+';
                    map[i + k][j * 4 + j * 2 + 1] = '-';
                    map[i + k][j * 4 + j * 2 + 2] = '-';
                    map[i + k][j * 4 + j * 2 + 3] = '-';
                    map[i + k + 1][j * 4 + j * 2] = '/';
                    map[i + k + 1][j * 4 + j * 2 + 1] = ' ';
                    map[i + k + 1][j * 4 + j * 2 + 2] = ' ';
                    map[i + k + 1][j * 4 + j * 2 + 3] = '/';
                    map[i + k + 1][j * 4 + j * 2 + 4] = '|';
                    map[i + k + 2][j * 4 + j * 2] = '+';
                    map[i + k + 2][j * 4 + j * 2 + 1] = '-';
                    map[i + k + 2][j * 4 + j * 2 + 2] = '-';
                    map[i + k + 2][j * 4 + j * 2 + 3] = '-';
                    map[i + k + 2][j * 4 + j * 2 + 4] = '|';
                    map[i + k + 3][j * 4 + j * 2 + 1] = ' ';
                    map[i + k + 3][j * 4 + j * 2 + 2] = ' ';
                    map[i + k + 3][j * 4 + j * 2 + 3] = '/';
                    map[i + k + 3][j * 4 + j * 2 + 4] = '+';
                    map[i + k + 4][j * 4 + j * 2] = '+';
                    map[i + k + 4][j * 4 + j * 2 + 1] = '-';
                    map[i + k + 4][j * 4 + j * 2 + 2] = '-';
                    map[i + k + 4][j * 4 + j * 2 + 3] = '-';
                    map[i + k + 4][j * 4 + j * 2 + 4] = '+';
                }
            }
        }
    }
    
    // 输出结果矩阵
    height = max_height + m + 1;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}