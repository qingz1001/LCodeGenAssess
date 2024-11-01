#include <stdio.h>
#include <string.h>

int n, m;
char grid[35][35];
int ans;

void dfs(int x, int y, int l, int r, int u, int d) {
    if (x == n) {
        ans++;
        return;
    }
    if (grid[x][y] == '#') {
        dfs(x + (y == m - 1), (y == m - 1) ? 0 : y + 1, l, r, u, d);
    } else {
        if (l) dfs(x + 1, y, 0, r, u, d);
        if (r) dfs(x + 1, y, l, 0, u, d);
        if (u) dfs(x, y + 1, l, r, 0, d);
        if (d) dfs(x, y + 1, l, r, u, 0);
        if (l && r && u && d) {
            grid[x][y] = '#';
            dfs(x + 1, y, 0, r, 0, d);
            dfs(x + 1, y, l, 0, 0, d);
            dfs(x + 1, y, l, r, 0, 0);
            dfs(x, y + 1, 0, r, u, 0);
            dfs(x, y + 1, l, 0, u, 0);
            dfs(x, y + 1, l, r, 0, d);
            grid[x][y] = '.';
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    dfs(0, 0, 1, 1, 1, 1);
    printf("%d\n", ans);
    return 0;
}