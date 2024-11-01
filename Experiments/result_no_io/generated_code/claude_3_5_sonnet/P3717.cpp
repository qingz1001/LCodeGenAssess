#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100

bool grid[MAX_N + 1][MAX_N + 1];

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                if (dx * dx + dy * dy <= r * r) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                        grid[nx][ny] = true;
                    }
                }
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j]) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}