#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 2001

int n, k, r;
int w[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int dp[MAXN][MAXN][2];

void dfs(int u, int fa) {
    dp[u][0][0] = 0;
    dp[u][1][1] = w[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        for (int j = k; j >= 1; j--) {
            for (int l = j; l >= 0; l--) {
                dp[u][j][0] = dp[u][j][0] + dp[v][l][1];
                if (j - l - 1 >= 0) dp[u][j][0] = dp[u][j][0] + dp[v][l][0];
                if (j - l >= 0) dp[u][j][1] = dp[u][j][1] + dp[v][l][0];
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &k, &r);
        edge_cnt = 0;
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs(1, 0);
        int ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = ans + dp[1][i][1];
        }
        printf("%d\n", ans);
    }
    return 0;
}