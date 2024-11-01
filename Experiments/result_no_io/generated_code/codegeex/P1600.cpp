#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MAXM 600005

int n, m, w[MAXN], ans[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], cnt;

void add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int dep[MAXN], fa[MAXN], son[MAXN], siz[MAXN], top[MAXN], dfn[MAXN], idx;

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

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++idx;
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
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct Node {
    int s, t, d;
} a[MAXN];

int cmp(const void *x, const void *y) {
    Node *p = (Node *)x, *q = (Node *)y;
    return p->d - q->d;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i].s, &a[i].t);
        a[i].d = dep[a[i].s] + dep[a[i].t] - 2 * dep[lca(a[i].s, a[i].t)];
    }
    qsort(a + 1, m + 1, sizeof(Node), cmp);
    for (int i = 1, j = 1; i <= n; i++) {
        for (; j <= m && a[j].d <= w[i]; j++) {
            ans[i]++;
        }
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}