#include <stdio.h>
#include <stdlib.h>

#define MAX_N 105

int n, m;
char grid[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == '-') return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == '#') {
                s++;
                dfs(i, j);
            }
        }
    }

    printf("%d\n", s);

    return 0;
}