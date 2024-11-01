#include <stdio.h>
#include <stdlib.h>

#define MOD 11192869

int n, m;
int T[4][51];
int L[2501];
int dp[4][51][2];

void dfs(int x, int y, int last, int pos) {
    if (pos == n * m) {
        dp[x][y][last]++;
        return;
    }
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && T[nx][ny] == L[pos]) {
            dfs(nx, ny, L[pos], pos + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    for (int i = 0; i < n * m; i++) {
        scanf("%d", &L[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 || i == n || j == 1 || j == m) {
                dfs(i, j, T[i][j], 0);
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += dp[i][j][T[i][j]];
            ans %= MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}