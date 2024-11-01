#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

int n, m, c, op;
char grid[10][10];
int dp[10][10][10][10][2];

void dfs(int x, int y, int dx, int dy, int color, int dir) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '#') return;
    if (dp[x][y][dx][dy][dir] != -1) return;

    dp[x][y][dx][dy][dir] = (dp[x][y][dx][dy][dir] + 1) % MOD;

    int nx = x + dx, ny = y + dy;
    dfs(nx, ny, dx, dy, color, dir);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &c, &op);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                for (int k = 0; k < c; k++) {
                    dfs(i, j, 0, 1, k, 0); // right
                    dfs(i, j, 1, 0, k, 0); // down
                    dfs(i, j, 0, -1, k, 0); // left
                    dfs(i, j, -1, 0, k, 0); // up
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                for (int k = 0; k < c; k++) {
                    ans = (ans + dp[i][j][0][1][k]) % MOD;
                    ans = (ans + dp[i][j][1][0][k]) % MOD;
                    ans = (ans + dp[i][j][0][-1][k]) % MOD;
                    ans = (ans + dp[i][j][-1][0][k]) % MOD;
                }
            }
        }
    }

    if (op == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '.') {
                    for (int k = 0; k < c; k++) {
                        dfs(n - i - 1, m - j - 1, 0, 1, k, 0); // right
                        dfs(n - i - 1, m - j - 1, 1, 0, k, 0); // down
                        dfs(n - i - 1, m - j - 1, 0, -1, k, 0); // left
                        dfs(n - i - 1, m - j - 1, -1, 0, k, 0); // up
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '.') {
                    for (int k = 0; k < c; k++) {
                        ans = (ans + dp[n - i - 1][m - j - 1][0][1][k]) % MOD;
                        ans = (ans + dp[n - i - 1][m - j - 1][1][0][k]) % MOD;
                        ans = (ans + dp[n - i - 1][m - j - 1][0][-1][k]) % MOD;
                        ans = (ans + dp[n - i - 1][m - j - 1][-1][0][k]) % MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}