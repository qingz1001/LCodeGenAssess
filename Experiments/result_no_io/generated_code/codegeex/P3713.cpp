#include <stdio.h>
#include <string.h>

#define MOD 1000000009

char grid[31][31];
int m, n;
int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int dp[31][31][31][31][2];

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%s", grid[i] + 1);
    }

    long long ans = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == '*') {
                for (int k = 1; k <= m; k++) {
                    for (int l = 1; l <= n; l++) {
                        if (grid[k][l] == '*') {
                            for (int d = 0; d < 8; d++) {
                                int nx = i + dx[d], ny = j + dy[d];
                                int mx = k + dx[d], my = l + dy[d];
                                if (nx >= 1 && nx <= m && ny >= 1 && ny <= n && mx >= 1 && mx <= m && my >= 1 && my <= n && grid[nx][ny] == '*' && grid[mx][my] == '*') {
                                    dp[i][j][k][l][0] = (dp[i][j][k][l][0] + dp[nx][ny][mx][my][1]) % MOD;
                                    dp[i][j][k][l][1] = (dp[i][j][k][l][1] + dp[nx][ny][mx][my][0]) % MOD;
                                }
                            }
                            dp[i][j][k][l][0] = (dp[i][j][k][l][0] + 1) % MOD;
                            dp[i][j][k][l][1] = (dp[i][j][k][l][1] + 1) % MOD;
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                for (int l = 1; l <= n; l++) {
                    if (grid[i][j] == '*' && grid[k][l] == '*') {
                        ans = (ans + (long long)dp[i][j][k][l][0] * dp[i][j][k][l][1]) % MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}