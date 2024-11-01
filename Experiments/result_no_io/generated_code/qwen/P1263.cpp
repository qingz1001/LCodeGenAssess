#include <stdio.h>
#include <stdlib.h>

#define MAXN 205

int m, n;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 0 || visited[x][y]) return;
    visited[x][y] = 1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny] && grid[nx][ny] == 0) {
                dfs(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && visited[i][j]) {
                printf("%d %d\n", i + 1, j + 1);
            }
        }
    }

    return 0;
}