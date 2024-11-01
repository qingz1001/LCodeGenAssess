#include <stdio.h>
#include <stdlib.h>

#define MOD 11192869

int n, m;
int T[4][51];
int L[2501];
int dp[3][51][51];

void dfs(int x, int y, int last, int len) {
    if (len == n * m) {
        dp[last][x][y]++;
        return;
    }
    if (dp[last][x][y]) return;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && T[nx][ny] != L[len]) {
            dfs(nx, ny, 1 - last, len + 1);
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

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                dp[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (T[i][1] == L[0]) dfs(i, 1, 1, 1);
        if (T[i][m] == L[0]) dfs(i, m, 1, 1);
    }
    for (int j = 1; j <= m; j++) {
        if (T[1][j] == L[0]) dfs(1, j, 1, 1);
        if (T[n][j] == L[0]) dfs(n, j, 1, 1);
    }

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            result += dp[0][i][j];
            result %= MOD;
        }
    }

    printf("%lld\n", result);

    return 0;
}