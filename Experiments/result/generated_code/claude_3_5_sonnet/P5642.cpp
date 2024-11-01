#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MOD 998244353

int n, m;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN];
int w[MAXN], id[MAXN], cnt;
int st[MAXN][20], lg[MAXN];
long long sum[MAXN * 4], tag[MAXN * 4];

void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
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
    id[u] = ++cnt;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void build(int p, int l, int r) {
    if (l == r) {
        sum[p] = w[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void pushdown(int p, int l, int r) {
    if (!tag[p]) return;
    int mid = (l + r) >> 1;
    sum[p << 1] += (mid - l + 1) * tag[p];
    sum[p << 1 | 1] += (r - mid) * tag[p];
    tag[p << 1] += tag[p];
    tag[p << 1 | 1] += tag[p];
    tag[p] = 0;
}

void update(int p, int l, int r, int x, int y, long long v) {
    if (x <= l && r <= y) {
        sum[p] += (r - l + 1) * v;
        tag[p] += v;
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid) update(p << 1, l, mid, x, y, v);
    if (y > mid) update(p << 1 | 1, mid + 1, r, x, y, v);
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

long long query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[p];
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (x <= mid) res += query(p << 1, l, mid, x, y);
    if (y > mid) res += query(p << 1 | 1, mid + 1, r, x, y);
    return res;
}

void modify(int u, int v, long long x) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        update(1, 1, n, id[top[u]], id[u], x);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    update(1, 1, n, id[u], id[v], x);
}

long long get(int u, int v) {
    long long res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        res += query(1, 1, n, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    res += query(1, 1, n, id[u], id[v]);
    return res;
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        modify(u, v, w);
    }
    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            int l = lca(u, v);
            long long sum = get(u, l) + get(v, l) - get(l, l);
            long long left = 0, right = 1e9;
            while (left < right) {
                long long mid = (left + right) >> 1;
                if (sum + mid > get(u, v)) right = mid;
                else left = mid + 1;
            }
            ans = (ans + left) % MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}