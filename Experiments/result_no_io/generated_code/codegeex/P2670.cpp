#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 100

// 检查坐标是否在雷区内
bool isValid(int n, int m, int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// 计算每个非地雷格周围的地雷数
void calculateMines(int n, int m, char grid[MAX_N][MAX_M], int result[MAX_N][MAX_M]) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                result[i][j] = -1; // 地雷格标记为-1
            } else {
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int nx = i + directions[k][0];
                    int ny = j + directions[k][1];
                    if (isValid(n, m, nx, ny) && grid[nx][ny] == '*') {
                        count++;
                    }
                }
                result[i][j] = count;
            }
        }
    }
}

// 打印结果
void printResult(int n, int m, int result[MAX_N][MAX_M]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (result[i][j] == -1) {
                printf("*");
            } else {
                printf("%d", result[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    char grid[MAX_N][MAX_M];
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    int result[MAX_N][MAX_M];
    calculateMines(n, m, grid, result);
    printResult(n, m, result);
    
    return 0;
}