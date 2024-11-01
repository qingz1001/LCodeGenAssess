#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    // 初始化地图，0表示未照亮，1表示照亮
    int map[n+2][n+2];
    for (int i = 0; i <= n+1; i++) {
        for (int j = 0; j <= n+1; j++) {
            map[i][j] = 0;
        }
    }

    // 处理火把的照亮范围
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                    if (dx == -2 || dx == 2 || dy == -2 || dy == 2) {
                        map[nx][ny] = 1;
                    } else {
                        if (dx == -1 || dx == 1 || dy == -1 || dy == 1) {
                            map[nx][ny] = 1;
                        }
                    }
                }
            }
        }
    }

    // 处理萤石的照亮范围
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                    map[nx][ny] = 1;
                }
            }
        }
    }

    // 统计怪物生成的点数
    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == 0) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}