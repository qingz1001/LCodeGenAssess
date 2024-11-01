#include <stdio.h>
#include <stdlib.h>

#define MAXN 300001
#define MAXM 300001

int n, m;
int w[MAXN];
int head[MAXN], nxt[MAXM], to[MAXM], cnt;

void add(int u, int v) {
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

int d[MAXN], f[MAXN], g[MAXN];

void dfs1(int u, int fa) {
    d[u] = d[fa] + 1;
    f[u] = fa;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs2(v, u);
        g[u] += g[v];
    }
    if (w[u] >= d[u] && w[u] <= d[u] + g[u]) {
        g[u]++;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    dfs1(1, 0);
    for (int i = 1; i <= m; i++) {
        int s, t;
        scanf("%d%d", &s, &t);
        int u = s, v = t;
        while (u != v) {
            if (d[u] > d[v]) {
                u = f[u];
            } else {
                v = f[v];
            }
        }
        g[u]++;
    }
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        printf("%d ", g[i]);
    }
    return 0;
}