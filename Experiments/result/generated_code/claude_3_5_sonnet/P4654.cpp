#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 2000005

int n, t, m;
int head[MAXN], to[MAXM], nxt[MAXM], tot;
int dep[MAXN], fa[MAXN], siz[MAXN], son[MAXN], top[MAXN];
int dfn[MAXN], rnk[MAXN], cnt;

void addedge(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    to[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
}

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u] = f;
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int tmp = u; u = v; v = tmp;
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    scanf("%d%d%d", &n, &t, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int l = lca(t, m);
    int ans = dep[t] + dep[m] - 2 * dep[l];
    printf("%d\n", ans);
    return 0;
}