#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100

bool grid[MAX_N][MAX_N];

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);

    // 初始化网格
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = false;
        }
    }

    // 处理每个探测器
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // 将坐标转换为从0开始

        // 标记探测器覆盖的区域
        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    grid[nx][ny] = true;
                }
            }
        }
    }

    // 计算被探测到的点的数量
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}