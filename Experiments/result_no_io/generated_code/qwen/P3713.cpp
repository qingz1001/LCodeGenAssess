#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000009

int m, n;
char grid[35][35];
int dp[35][35][35][35];

int dfs(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return 1;
    if (dp[x1][y1][x2][y2] != -1) return dp[x1][y2][x2][y2];

    int ans = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (abs(dx) + abs(dy) > 1) continue;
            int nx1 = x1 + dx, ny1 = y1 + dy;
            int nx2 = x2 + dx, ny2 = y2 + dy;
            if (nx1 >= 0 && nx1 < m && ny1 >= 0 && ny1 < n && nx2 >= 0 && nx2 < m && ny2 >= 0 && ny2 < n && grid[nx1][ny1] == grid[nx2][ny2]) {
                ans = (ans + dfs(nx1, ny1, nx2, ny2)) % MOD;
            }
        }
    }

    return dp[x1][y1][x2][y2] = ans;
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i) {
        scanf("%s", grid[i]);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                for (int l = 0; l < n; ++l) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }

    long long total_weight = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                for (int l = 0; l < n; ++l) {
                    if (grid[i][j] == grid[k][l] && abs(i - k) + abs(j - l) == 1) {
                        total_weight = (total_weight + dfs(i, j, k, l)) % MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", total_weight);

    return 0;
}