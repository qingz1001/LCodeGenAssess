#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

int n, e, m;
int *adj, *deg, *fa, *dp, *f, *g, *s, *v, *w;

void dfs(int x) {
    dp[x] = 1;
    s[x] = 1;
    for (int i = adj[x]; i; i = adj[i]) {
        if (fa[i] != i) {
            dfs(i);
            dp[x] = 1LL * dp[x] * (dp[i] + 1) % MOD;
            s[x] = (s[x] + s[i]) % MOD;
        }
    }
}

void dfs2(int x) {
    for (int i = adj[x]; i; i = adj[i]) {
        if (fa[i] != i) {
            f[i] = (1LL * f[x] * (dp[i] + 1) + (1LL * (deg[x] - 1) * f[i] + g[i]) % MOD * s[x]) % MOD;
            g[i] = (1LL * (deg[x] - 1) * g[i] + 1LL * (s[x] - s[i]) * (dp[i] + 1) + g[x]) % MOD;
            dfs2(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    adj = (int *)calloc(n + 1, sizeof(int));
    deg = (int *)calloc(n + 1, sizeof(int));
    fa = (int *)calloc(n + 1, sizeof(int));
    dp = (int *)calloc(n + 1, sizeof(int));
    f = (int *)calloc(n + 1, sizeof(int));
    g = (int *)calloc(n + 1, sizeof(int));
    s = (int *)calloc(n + 1, sizeof(int));
    v = (int *)calloc(n + 1, sizeof(int));
    w = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= e; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x] = y;
        deg[x]++;
        fa[y] = x;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        for (int j = 1; j <= x; j++) {
            int y;
            scanf("%d", &y);
            v[y] = 1;
        }
        scanf("%d", &x);
        int k = 0;
        for (int j = 1; j <= n; j++) {
            if (v[j]) {
                w[++k] = j;
                v[j] = k;
            }
        }
        dfs(x);
        f[x] = 0;
        g[x] = 0;
        dfs2(x);
        printf("%d\n", f[x]);
        for (int j = 1; j <= k; j++) {
            v[w[j]] = j;
        }
        memset(v, 0, sizeof(v));
    }
    free(adj);
    free(deg);
    free(fa);
    free(dp);
    free(f);
    free(g);
    free(s);
    free(v);
    free(w);
    return 0;
}