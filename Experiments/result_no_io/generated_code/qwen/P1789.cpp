#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_MK 25

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int lights[MAX_N][MAX_N] = {0};

    // Place lights from torches
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    lights[nx][ny] = 1;
                }
            }
        }
    }

    // Place lights from obsidian
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    lights[nx][ny] = 1;
                }
            }
        }
    }

    int monster_points = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lights[i][j] == 0) {
                ++monster_points;
            }
        }
    }

    printf("%d\n", monster_points);

    return 0;
}