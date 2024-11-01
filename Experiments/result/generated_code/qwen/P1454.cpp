#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

int n, m;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '-' || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                s++;
            }
        }
    }

    printf("%d\n", s);
    return 0;
}