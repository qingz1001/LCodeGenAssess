#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 20
#define MAX_C 50

int n, m, c;
int p[MAX_C + 1];
int grid[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, int color) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != color) {
        return;
    }
    grid[x][y] = 0;
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i], color);
    }
}

int count_borders() {
    int borders = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) continue;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m || grid[ni][nj] != grid[i][j]) {
                    borders++;
                }
            }
        }
    }
    return borders / 2;
}

void fill_grid() {
    int color = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            while (p[color] == 0) color++;
            grid[i][j] = color;
            p[color]--;
        }
    }
}

void optimize() {
    int best_borders = count_borders();
    int best_grid[MAX_N][MAX_M];
    memcpy(best_grid, grid, sizeof(grid));

    for (int iter = 0; iter < 1000; iter++) {
        int x1 = rand() % n, y1 = rand() % m;
        int x2 = rand() % n, y2 = rand() % m;
        if (grid[x1][y1] == grid[x2][y2]) continue;

        int temp = grid[x1][y1];
        grid[x1][y1] = grid[x2][y2];
        grid[x2][y2] = temp;

        int new_borders = count_borders();
        if (new_borders < best_borders) {
            best_borders = new_borders;
            memcpy(best_grid, grid, sizeof(grid));
        } else {
            temp = grid[x1][y1];
            grid[x1][y1] = grid[x2][y2];
            grid[x2][y2] = temp;
        }
    }

    memcpy(grid, best_grid, sizeof(grid));
}

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 1; i <= c; i++) {
        scanf("%d", &p[i]);
    }

    fill_grid();
    optimize();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}