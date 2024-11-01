#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

int n, m, q;
int head[MAXN], to[MAXM*2], nxt[MAXM*2], tot;
int dfn[MAXN], low[MAXN], fa[MAXN], dep[MAXN], son[MAXN], siz[MAXN], top[MAXN];
int timer;

void addEdge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int u, int f) {
    dfn[u] = ++timer;
    low[u] = dfn[u];
    fa[u] = f;
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        if (!dfn[v]) {
            dfs1(v, u);
            siz[u] += siz[v];
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        } else if (dfn[v] < dfn[u]) {
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    
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

int query1(int a, int b, int g1, int g2) {
    if (fa[g1] == g2) {
        int tmp = g1; g1 = g2; g2 = tmp;
    }
    if (fa[g2] != g1) return 1;
    if (lca(a, b) != g1) return 1;
    if ((lca(a, g2) == g2) ^ (lca(b, g2) == g2)) return 1;
    return 0;
}

int query2(int a, int b, int c) {
    if (lca(a, b) != c) return 1;
    if ((lca(a, c) == c) && (lca(b, c) == c)) return 0;
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    scanf("%d", &q);
    while (q--) {
        int type, a, b, c, d;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            printf(query1(a, b, c, d) ? "yes\n" : "no\n");
        } else {
            scanf("%d%d%d", &a, &b, &c);
            printf(query2(a, b, c) ? "yes\n" : "no\n");
        }
    }
    
    return 0;
}