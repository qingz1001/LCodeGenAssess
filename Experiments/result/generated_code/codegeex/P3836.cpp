#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

int main() {
    int m, n, k;
    char garden[MAX_SIZE][MAX_SIZE];

    // 读取输入
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", garden[i]);
    }

    // 构造迷宫
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (garden[i][j] == '.') {
                // 检查四个方向的邻居
                int count = 0;
                if (i > 0 && garden[i-1][j] == '.') count++;
                if (i < m-1 && garden[i+1][j] == '.') count++;
                if (j > 0 && garden[i][j-1] == '.') count++;
                if (j < n-1 && garden[i][j+1] == '.') count++;

                // 如果这个空格有且只有一个邻居，则种植灌木
                if (count == 1) {
                    garden[i][j] = 'X';
                }
            }
        }
    }

    // 输出迷宫
    for (int i = 0; i < m; i++) {
        printf("%s\n", garden[i]);
    }

    return 0;
}