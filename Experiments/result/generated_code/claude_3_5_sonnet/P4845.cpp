#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1005
#define MAX_K 1005
#define MAX_R 1005

int n, k, r;
int w[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], cnt;
int dp[MAX_N][MAX_K];
int sum[MAX_N], size[MAX_N], f[MAX_N], g[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    sum[u] = w[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        sum[u] += sum[v];
    }
}

void dfs2(int u, int fa) {
    f[u] = g[u] = w[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs2(v, u);
        if (r > 1) {
            f[u] += f[v];
            g[u] += g[v];
        }
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        if (r > 1) {
            f[u] = f[u] - f[v] + g[v];
        }
    }
}

void dfs3(int u, int fa) {
    for (int i = 1; i <= k; i++) {
        dp[u][i] = f[u];
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs3(v, u);
        for (int j = k; j >= 1; j--) {
            for (int l = 0; l < j; l++) {
                if (dp[u][j] < dp[u][j-l-1] + dp[v][l]) {
                    dp[u][j] = dp[u][j-l-1] + dp[v][l];
                }
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(head, 0, sizeof(head));
        memset(dp, 0, sizeof(dp));
        cnt = 0;

        scanf("%d %d %d", &n, &k, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
        }
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }

        dfs1(1, 0);
        dfs2(1, 0);
        dfs3(1, 0);

        printf("%d\n", dp[1][k]);
    }
    return 0;
}