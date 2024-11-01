#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

const int MAXN = 500005;
int n;
double k;
ll d[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], cnt;
ll val[MAXN * 2], sum[MAXN], tag[MAXN];
int size[MAXN], son[MAXN], fa[MAXN], top[MAXN], dep[MAXN], dfn[MAXN], idx;

void add(int u, int v, ll w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u) {
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++idx;
    if (son[u]) dfs2(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int u) {
    sum[u] = sum[son[u]] + tag[u] * size[u];
}

void pushdown(int u) {
    if (tag[u]) {
        tag[son[u]] += tag[u];
        sum[son[u]] += tag[u] * size[son[u]];
        tag[u] = 0;
    }
}

void modify(int u, int l, int r, ll v) {
    if (l <= 1 && r >= size[u]) {
        sum[u] = v * size[u];
        tag[u] = v;
        return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (size[son[u]] >= mid) modify(son[u], l, mid, v);
    else modify(u, mid, r, v);
    pushup(u);
}

ll query(int u, int l, int r) {
    if (l <= 1 && r >= size[u]) return sum[u];
    pushdown(u);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (size[son[u]] >= mid) res = query(son[u], l, mid);
    else res = query(u, mid, r);
    return res;
}

void update(int x, int y, ll v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        modify(1, dfn[top[x]], dfn[x], v);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        x ^= y ^= x ^= y;
    }
    modify(1, dfn[x], dfn[y], v);
}

ll query_sum(int x, int y) {
    ll res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        res += query(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        x ^= y ^= x ^= y;
    }
    res += query(1, dfn[x], dfn[y]);
    return res;
}

int main() {
    scanf("%d%lf", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", &d[i]);
    for (int i = 2; i <= n; i++) add((int)(i / k), i, d[i]);
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        if (fa[i]) {
            update(i, fa[i], d[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%lld ", query_sum(i, (int)(i / k)));
    }
    return 0;
}