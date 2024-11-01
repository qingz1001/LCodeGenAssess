#include <stdio.h>
#include <stdlib.h>

#define MAXN 35
#define MAXM 35

int n, m;
char grid[MAXN][MAXM];
int dp[MAXN][MAXM];

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '.';
}

int count_ways(int x, int y) {
    if (x >= n || y >= m || grid[x][y] != '.') return 0;
    if (dp[x][y] != -1) return dp[x][y];

    int ways = 0;

    // Place an L shape starting at (x, y)
    for (int dx = 1; dx <= n - x; ++dx) {
        for (int dy = 1; dy <= m - y; ++dy) {
            if (is_valid(x + dx, y) && is_valid(x, y + dy)) {
                if (!is_valid(x + dx, y + dy)) break;
                ways += count_ways(x + dx, y + dy);
            }
        }
    }

    dp[x][y] = ways;
    return ways;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = -1;
        }
    }

    int total_ways = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                total_ways += count_ways(i, j);
            }
        }
    }

    printf("%d\n", total_ways);

    return 0;
}