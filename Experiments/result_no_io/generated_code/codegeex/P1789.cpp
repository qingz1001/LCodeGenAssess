#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int grid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 0; // 初始化网格
        }
    }

    // 火把照亮范围
    int torch_lights[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 2, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // 萤石照亮范围
    int glowstone_lights[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 2, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    // 火把位置
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    grid[nx][ny] = 2; // 2表示火把照亮
                }
            }
        }
    }

    // 萤石位置
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    grid[nx][ny] = 2; // 2表示萤石照亮
                }
            }
        }
    }

    // 统计怪物生成的点数
    int monster_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                monster_count++;
            }
        }
    }

    printf("%d\n", monster_count);
    return 0;
}