#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000009
#define MAX_N 30
#define MAX_M 30

int m, n;
char grid[MAX_M][MAX_N];
int dp[MAX_M][MAX_N][MAX_M][MAX_N];

int dfs(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];

    int res = 1;
    for (int dx1 = -1; dx1 <= 1; ++dx1) {
        for (int dy1 = -1; dy1 <= 1; ++dy1) {
            for (int dx2 = -1; dx2 <= 1; ++dx2) {
                for (int dy2 = -1; dy2 <= 1; ++dy2) {
                    int nx1 = x1 + dx1, ny1 = y1 + dy1;
                    int nx2 = x2 + dx2, ny2 = y2 + dy2;
                    if (nx1 < 0 || nx1 >= m || ny1 < 0 || ny1 >= n) continue;
                    if (nx2 < 0 || nx2 >= m || ny2 < 0 || ny2 >= n) continue;
                    if (grid[nx1][ny1] != grid[nx2][ny2]) continue;
                    res = (res + dfs(nx1, ny1, nx2, ny2)) % MOD;
                }
            }
        }
    }

    dp[x1][y1][x2][y2] = res;
    return res;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));

    int result = 0;
    for (int x1 = 0; x1 < m; ++x1) {
        for (int y1 = 0; y1 < n; ++y1) {
            for (int x2 = x1; x2 < m; ++x2) {
                for (int y2 = y1; y2 < n; ++y2) {
                    result = (result + dfs(x1, y1, x2, y2)) % MOD;
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}