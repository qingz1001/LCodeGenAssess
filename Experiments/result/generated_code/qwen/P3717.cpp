#include <stdio.h>
#include <math.h>

#define MAXN 105

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    int grid[MAXN][MAXN] = {0};

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        for (int j = -r; j <= r; j++) {
            for (int k = -r; k <= r; k++) {
                if (j * j + k * k <= r * r) {
                    int nx = x + j;
                    int ny = y + k;
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                        grid[nx][ny] = 1;
                    }
                }
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            count += grid[i][j];
        }
    }

    printf("%d\n", count);
    return 0;
}