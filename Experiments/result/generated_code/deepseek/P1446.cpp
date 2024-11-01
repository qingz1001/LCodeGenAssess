#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 61
#define MAXP 100

int S_r, S_b, S_g, m, P;
int n;
int shuffle[MAXN][MAXN];
int vis[MAXN];
int color[MAXN];
int dp[21][21][21];

int mod(int x) {
    return (x % P + P) % P;
}

int dfs(int u) {
    vis[u] = 1;
    int v = shuffle[0][u];
    if (vis[v]) return 1;
    return 1 + dfs(v);
}

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int len = dfs(i);
        for (int r = S_r; r >= 0; r--) {
            for (int b = S_b; b >= 0; b--) {
                for (int g = S_g; g >= 0; g--) {
                    int tmp = dp[r][b][g];
                    if (r >= len) dp[r][b][g] = mod(dp[r][b][g] + dp[r - len][b][g]);
                    if (b >= len) dp[r][b][g] = mod(dp[r][b][g] + dp[r][b - len][g]);
                    if (g >= len) dp[r][b][g] = mod(dp[r][b][g] + dp[r][b][g - len]);
                }
            }
        }
    }
    return dp[S_r][S_b][S_g];
}

int main() {
    scanf("%d %d %d %d %d", &S_r, &S_b, &S_g, &m, &P);
    n = S_r + S_b + S_g;
    for (int i = 1; i <= n; i++) shuffle[0][i] = i;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &shuffle[i][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        memset(vis, 0, sizeof(vis));
        ans = mod(ans + solve());
    }
    ans = mod(ans * mod(mod(mod(m + 1) * P) * P));
    printf("%d\n", ans);
    return 0;
}