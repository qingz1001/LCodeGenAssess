#include <stdio.h>
#include <string.h>

#define MAX_N 888

char grid[MAX_N*2][MAX_N*2];
int output[MAX_N*2+1][MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 消耗换行符

    // 读取输入
    for (int i = 0; i < 2*n; i++) {
        fgets(grid[i], sizeof(grid[i]), stdin);
    }

    // 处理上半部分
    for (int i = 0; i < n; i++) {
        int start = n - i - 1;
        for (int j = 0; j < 2*i+1; j++) {
            if (j % 2 == 0) {
                output[i][start + j/2] = (grid[i][start*2 + j] == '/');
            } else {
                output[n+i+1][start + j/2] = (grid[i][start*2 + j] == '\\');
            }
        }
    }

    // 处理下半部分
    for (int i = 0; i < n; i++) {
        int start = i;
        for (int j = 0; j < 2*(n-i)-1; j++) {
            if (j % 2 == 0) {
                output[n+i][start + j/2] = (grid[n+i][start*2 + j] == '\\');
            } else {
                output[2*n-i][start + j/2] = (grid[n+i][start*2 + j] == '/');
            }
        }
    }

    // 输出结果
    printf("%d\n", n);
    for (int i = 0; i < 2*n+1; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}