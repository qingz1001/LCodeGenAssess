#include <stdio.h>
#include <stdlib.h>

#define MAXN 205

int m, n;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 0 || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    int k = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && grid[i][j] == 0) {
                ++k;
                dfs(i, j);
            }
        }
    }

    printf("%d\n", k);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && grid[i][j] == 0) {
                printf("%d %d\n", i + 1, j + 1);
                dfs(i, j);
            }
        }
    }

    return 0;
}