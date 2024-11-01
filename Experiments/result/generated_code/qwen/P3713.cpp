#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000009

typedef struct {
    int x, y;
} Point;

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

int is_valid(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

void dfs(int x, int y, int m, int n, char **grid, int *visited, char *path, int path_len, int *count) {
    if (!is_valid(x, y, m, n)) return;
    if (visited[x][y]) return;
    visited[x][y] = 1;
    path[path_len] = grid[x][y];
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx == x || ny == y) {
            dfs(nx, ny, m, n, grid, visited, path, path_len + 1, count);
        }
    }
    visited[x][y] = 0;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    char **grid = (char **)malloc(m * sizeof(char *));
    for (int i = 0; i < m; i++) {
        grid[i] = (char *)malloc(n * sizeof(char));
        scanf(" %s", grid[i]);
    }

    int total_weight = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int visited[m][n];
            memset(visited, 0, sizeof(visited));
            char path[1000];
            dfs(i, j, m, n, grid, visited, path, 0, &total_weight);
        }
    }

    printf("%d\n", total_weight);

    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}