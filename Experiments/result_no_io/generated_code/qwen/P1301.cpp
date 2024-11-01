#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 100
#define DIRS 8

int n, m;
int grid[MAX_N][MAX_M];
int visited[MAX_N][MAX_M][DIRS];

int minSteps = INT_MAX;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void dfs(int x, int y, int steps, int lastDir) {
    if (x == n - 1 && y == m - 1) {
        minSteps = steps;
        return;
    }
    for (int d = 0; d < DIRS; ++d) {
        if (d != lastDir) {
            int nx = x + dx[d] * grid[x][y];
            int ny = y + dy[d] * grid[x][y];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny][d]) {
                visited[nx][ny][d] = 1;
                dfs(nx, ny, steps + 1, d);
                visited[nx][ny][d] = 0;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int d = 0; d < DIRS; ++d) {
        visited[0][0][d] = 1;
        dfs(0, 0, 1, d);
        visited[0][0][d] = 0;
    }

    if (minSteps == INT_MAX) {
        printf("NEVER\n");
    } else {
        printf("%d\n", minSteps);
    }

    return 0;
}