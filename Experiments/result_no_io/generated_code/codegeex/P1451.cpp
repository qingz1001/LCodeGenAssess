#include <stdio.h>
#include <string.h>

int n, m;
char grid[101][101];
int visited[101][101];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '0' || visited[x][y]) {
        return;
    }
    visited[x][y] = 1;
    dfs(x - 1, y); // up
    dfs(x + 1, y); // down
    dfs(x, y - 1); // left
    dfs(x, y + 1); // right
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int cell_count = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '0' && !visited[i][j]) {
                dfs(i, j);
                cell_count++;
            }
        }
    }

    printf("%d\n", cell_count);
    return 0;
}