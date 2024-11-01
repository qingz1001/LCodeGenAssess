#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000
#define MAXM 1000000000
#define MAXC 100000

int n, m, c;
int grid[MAXN][MAXM];
int visited[MAXN][MAXM];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || !grid[x][y] || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &c);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = 1;
                visited[i][j] = 0;
            }
        }
        for (int i = 0; i < c; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            grid[x][y] = 0;
        }
        dfs(0, 0);
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j]) {
                    count++;
                }
            }
        }
        if (count > 1) {
            printf("0\n");
        } else {
            printf("-1\n");
        }
    }
    return 0;
}