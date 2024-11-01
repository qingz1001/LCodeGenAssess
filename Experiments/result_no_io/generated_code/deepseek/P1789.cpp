#include <stdio.h>
#include <stdbool.h>

#define MAXN 100

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    bool grid[MAXN][MAXN] = {false};

    // 处理火把
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // 转换为0-based索引

        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    if (abs(dx) + abs(dy) <= 2) {
                        grid[nx][ny] = true;
                    }
                }
            }
        }
    }

    // 处理萤石
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // 转换为0-based索引

        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    grid[nx][ny] = true;
                }
            }
        }
    }

    // 计算没有光的地方
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!grid[i][j]) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}