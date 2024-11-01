#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXM 7

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][1 << (MAXN * MAXM)];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int x, int y, int visited, int sum) {
    if (__builtin_popcount(visited) >= 4 && x == 0 && y == 0) {
        return sum;
    }
    if (x < 0 || x >= n || y < 0 || y >= m || (visited & (1 << (x * m + y)))) {
        return -1e9;
    }
    if (dp[x][y][visited] != -1) {
        return dp[x][y][visited];
    }

    visited |= 1 << (x * m + y);
    int res = -1e9;
    res = max(res, dfs(x + 1, y, visited, sum + grid[x][y]));
    res = max(res, dfs(x - 1, y, visited, sum + grid[x][y]));
    res = max(res, dfs(x, y + 1, visited, sum + grid[x][y]));
    res = max(res, dfs(x, y - 1, visited, sum + grid[x][y]));
    visited ^= 1 << (x * m + y);

    dp[x][y][visited] = res;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < (1 << (n * m)); k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    int result = -1e9;
    result = max(result, dfs(0, 0, 1 << (0 * m + 0), grid[0][0]));

    printf("%d\n", result);
    return 0;
}