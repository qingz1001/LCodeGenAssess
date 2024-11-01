#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    char grid[n][m];
    int result[n][m];

    // 读取输入的雷区
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    // 初始化结果数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
        }
    }

    // 计算每个非地雷格周围的地雷数
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                result[i][j] = '*';
            } else {
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (i + x >= 0 && i + x < n && j + y >= 0 && j + y < m && grid[i + x][j + y] == '*') {
                            result[i][j]++;
                        }
                    }
                }
            }
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (result[i][j] == '*') {
                printf("*");
            } else {
                printf("%d", result[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}