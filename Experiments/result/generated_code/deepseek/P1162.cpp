#include <stdio.h>

#define MAXN 30

int n;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] == 1 || visited[x][y]) {
        return;
    }
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Mark the boundary 0s as visited
    for (int i = 0; i < n; i++) {
        dfs(0, i);
        dfs(n - 1, i);
        dfs(i, 0);
        dfs(i, n - 1);
    }

    // Fill the inner 0s with 2
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                grid[i][j] = 2;
            }
        }
    }

    // Print the result
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}