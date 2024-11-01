#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100001
#define MAXM 200001
#define MAXLOG 20

int n, m, root, tot;
int a[MAXN], fa[MAXN], son[MAXN], top[MAXN], size[MAXN], dep[MAXN], dfn[MAXN], pos[MAXN], rk[MAXN], w[MAXN];
int tree[MAXM], val[MAXM], head[MAXN], next[MAXM];

void add(int u, int v) {
    next[tot] = head[u];
    head[u] = tot;
    val[tot] = v;
    tot++;
}

void dfs1(int u, int f) {
    int i, v;
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    for (i = head[u]; i != -1; i = next[i]) {
        v = val[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    int i, v;
    top[u] = t;
    dfn[u] = ++tot;
    pos[tot] = u;
    rk[u] = tot;
    if (son[u]) dfs2(son[u], t);
    for (i = head[u]; i != -1; i = next[i]) {
        v = val[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void build(int o, int l, int r) {
    if (l == r) {
        tree[o] = w[pos[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    tree[o] = tree[o << 1] + tree[o << 1 | 1];
}

int query(int o, int l, int r, int k) {
    if (l == r) return pos[l];
    int mid = (l + r) >> 1;
    if (k <= tree[o << 1]) return query(o << 1, l, mid, k);
    else return query(o << 1 | 1, mid + 1, r, k - tree[o << 1]);
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) v = fa[top[v]];
        else u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int kth(int u, int v, int k) {
    int l = lca(u, v);
    int dis = rk[u] + rk[v] - (rk[l] << 1) + 1;
    return query(1, 1, n, k - dis);
}

int main() {
    int i, u, v, k, last = 0;
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (m--) {
        scanf("%d%d%d", &u, &v, &k);
        u ^= last;
        printf("%d\n", last = w[kth(u, v, k)]);
    }
    return 0;
}