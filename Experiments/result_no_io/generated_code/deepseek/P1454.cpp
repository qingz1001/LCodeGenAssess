#include <stdio.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 100

char grid[MAXN][MAXM];
bool visited[MAXN][MAXM];
int n, m;

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != '#' || visited[x][y]) {
        return;
    }
    visited[x][y] = true;
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '#') {
                dfs(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int pattern_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                pattern_count++;
            }
        }
    }

    printf("%d\n", pattern_count);
    return 0;
}