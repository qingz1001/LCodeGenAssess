#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MOD 1000000007

int n, m;
char materials[MAXN];
char eigen_string[MAXN];
int adj[MAXN][MAXN];
int dp[MAXN][MAXN];

void dfs(int u, int p, char *path, int len) {
    if (len == m) {
        for (int i = 0; i <= n - len; ++i) {
            dp[u][i] = (dp[u][i] + 1) % MOD;
        }
        return;
    }
    path[len] = materials[u];
    for (int v = 1; v <= n; ++v) {
        if (adj[u][v] && v != p) {
            dfs(v, u, path, len + 1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x][y] = adj[y][x] = 1;
    }
    scanf("%s%s", materials, eigen_string);

    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dfs(i, 0, (char *)malloc((m + 1) * sizeof(char)), 0);
        free((char *)malloc((m + 1) * sizeof(char)));
    }

    long long expectation = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n - m; ++j) {
            expectation = (expectation + dp[i][j]) % MOD;
        }
    }

    printf("%lld\n", expectation * n * n % MOD);
    return 0;
}