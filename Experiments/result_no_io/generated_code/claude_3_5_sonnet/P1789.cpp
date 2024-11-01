#include <stdio.h>
#include <string.h>

#define MAX_N 100

int n, m, k;
int grid[MAX_N][MAX_N];

void placeTorch(int x, int y) {
    for (int i = x - 2; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                if ((i == x && abs(j - y) <= 2) || (j == y && abs(i - x) <= 2) ||
                    (abs(i - x) == 1 && abs(j - y) == 1)) {
                    grid[i][j] = 1;
                }
            }
        }
    }
}

void placeGlowstone(int x, int y) {
    for (int i = x - 2; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                grid[i][j] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        placeTorch(x - 1, y - 1);
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        placeGlowstone(x - 1, y - 1);
    }

    int monsters = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                monsters++;
            }
        }
    }

    printf("%d\n", monsters);

    return 0;
}