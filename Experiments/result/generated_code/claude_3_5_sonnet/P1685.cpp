#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 50001
#define MOD 10000

typedef long long ll;

int n, m, s, t, t0;
int head[MAX_N], nxt[MAX_M], to[MAX_M], weight[MAX_M], cnt;
ll f[MAX_N], g[MAX_N];
int vis[MAX_N];

void add_edge(int u, int v, int w) {
    to[++cnt] = v;
    weight[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs1(v);
        f[u] = (f[u] + f[v]) % MOD;
    }
    if (u == t) f[u] = 1;
}

void dfs2(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        g[v] = (g[v] + g[u] * weight[i] % MOD) % MOD;
        dfs2(v);
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &t0);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }

    dfs1(s);
    g[s] = 1;
    dfs2(s);

    ll ans = g[t] * f[s] % MOD;
    ans = (ans * t0 % MOD * f[s] % MOD + g[t]) % MOD;
    printf("%lld\n", ans);

    return 0;
}