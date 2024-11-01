#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30010
#define MAXM 60010

int n, q, cnt, root;
int w[MAXN], fa[MAXN], size[MAXN], son[MAXN], top[MAXN], dep[MAXN], dfn[MAXN], id[MAXN];
int head[MAXN], nxt[MAXM], to[MAXM];
int sum[MAXN], max[MAXN], tag[MAXN];

void add(int u, int v) {
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

void dfs1(int u) {
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++cnt;
    id[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushdown(int u) {
    if (!tag[u]) return;
    max[u] += tag[u];
    if (son[u]) max[son[u]] += tag[u];
    tag[u] = 0;
}

void pushup(int u) {
    max[u] = w[u];
    if (son[u]) max[u] = max(max[u], max[son[u]]);
}

void update(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
        pushdown(id[dfn[top[u]]]);
        sum[id[dfn[top[u]]]] += k * (dfn[u] - dfn[top[u]] + 1);
        pushup(id[dfn[top[u]]]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) u ^= v ^= u ^= v;
    pushdown(id[dfn[u]]);
    sum[id[dfn[u]]] += k * (dfn[v] - dfn[u] + 1);
    pushup(id[dfn[u]]);
}

int query(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
        pushdown(id[dfn[top[u]]]);
        res = max(res, max[id[dfn[top[u]]]]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) u ^= v ^= u ^= v;
    pushdown(id[dfn[u]]);
    res = max(res, max[id[dfn[u]]]);
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        pushdown(id[i]);
        sum[id[i]] += w[i];
        pushup(id[i]);
    }
    scanf("%d", &q);
    char op[10];
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'C') {
            int u, t;
            scanf("%d%d", &u, &t);
            update(u, u, t - w[u]);
            w[u] = t;
        } else if (op[1] == 'S') {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", query(u, v));
        } else {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", sum[u] + sum[v] - sum[fa[root]] * 2);
        }
    }
    return 0;
}