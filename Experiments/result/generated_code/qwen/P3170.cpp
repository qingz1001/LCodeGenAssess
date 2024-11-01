#include <stdio.h>
#include <stdlib.h>

#define MAXN 31

int n, m;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN];

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '.';
}

void dfs(int x, int y, int dir, int len) {
    if (len > 0 && !is_valid(x, y)) return;
    if (len > 0) dp[x][y]++;
    if (dir == 0) { // right
        dfs(x, y + 1, 0, len + 1);
        dfs(x, y - 1, 2, 1);
    } else if (dir == 1) { // down
        dfs(x + 1, y, 1, len + 1);
        dfs(x - 1, y, 3, 1);
    } else if (dir == 2) { // left
        dfs(x, y - 1, 2, len + 1);
        dfs(x, y + 1, 0, 1);
    } else if (dir == 3) { // up
        dfs(x - 1, y, 3, len + 1);
        dfs(x + 1, y, 1, 1);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                dfs(i, j, 0, 0);
                dfs(i, j, 1, 0);
                dfs(i, j, 2, 0);
                dfs(i, j, 3, 0);
            }
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            total += dp[i][j];
        }
    }

    printf("%lld\n", total);

    return 0;
}