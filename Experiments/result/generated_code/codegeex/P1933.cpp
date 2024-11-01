#include <stdio.h>
#include <string.h>

#define MOD 11192869

int n, m;
int T[4][51], L[51];
int dp[4][51][51][2];
int cnt[4][51][51][2];

void dfs(int x, int y, int t, int sum, int prev) {
    if (x < 1 || x > n || y < 1 || y > m || T[x][y] != L[sum]) return;
    if (dp[x][y][t][prev] > sum) return;
    dp[x][y][t][prev] = sum;
    cnt[x][y][t][prev] = 1;
    if (x > 1) dfs(x - 1, y, t + 1, sum + 1, 0);
    if (x < n) dfs(x + 1, y, t + 1, sum + 1, 0);
    if (y > 1) dfs(x, y - 1, t + 1, sum + 1, 1);
    if (y < m) dfs(x, y + 1, t + 1, sum + 1, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    for (int i = 1; i <= n * m; i++) {
        scanf("%d", &L[i]);
    }

    memset(dp, -1, sizeof(dp));
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (T[i][j] == L[1]) {
                dfs(i, j, 1, 1, 0);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (T[i][j] == L[n * m]) {
                ans = (ans + cnt[i][j][n * m - 1][0] + cnt[i][j][n * m - 1][1]) % MOD;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}