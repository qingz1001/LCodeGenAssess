#include <stdio.h>
#include <string.h>

#define MOD 1000000009
#define MAXN 30

int m, n;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int dfs(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];

    int res = 1;
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (i == x1 && j == y1) continue;
            if (grid[i][j] == grid[x1][y1]) {
                res = (res + dfs(x1 + 1, y1, i, j) + dfs(x1, y1 + 1, i, j) + dfs(x1, y1, i - 1, j) + dfs(x1, y1, i, j - 1)) % MOD;
            }
        }
    }

    dp[x1][y1][x2][y2] = res;
    return res;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));

    int result = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result = (result + dfs(i, j, m - 1, n - 1)) % MOD;
        }
    }

    printf("%d\n", result);
    return 0;
}