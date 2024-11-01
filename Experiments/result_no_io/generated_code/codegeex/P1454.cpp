#include <stdio.h>
#include <string.h>

#define MAXN 101

int n, m;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    static int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    visited[x][y] = 1;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '#' && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int count = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}