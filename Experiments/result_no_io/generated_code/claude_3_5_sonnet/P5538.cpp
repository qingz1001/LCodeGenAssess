#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MOD 786433

typedef long long ll;

int n;
int a[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;
int sz[MAXN], dep[MAXN], fa[MAXN], top[MAXN], son[MAXN];
int id[MAXN], rid[MAXN], cnt;
int val[MAXN * 4], lazy[MAXN * 4];

void addedge(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}

void dfs1(int u, int f) {
    sz[u] = 1; fa[u] = f; dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t; id[u] = ++cnt; rid[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    val[rt] = val[rt << 1] & val[rt << 1 | 1];
}

void pushdown(int rt) {
    if (lazy[rt]) {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        val[rt << 1] = val[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        val[rt] = a[rid[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return val[rt];
    pushdown(rt);
    int mid = (l + r) >> 1, ans = (1 << 30) - 1;
    if (L <= mid) ans &= query(rt << 1, l, mid, L, R);
    if (R > mid) ans &= query(rt << 1 | 1, mid + 1, r, L, R);
    return ans;
}

int queryPath(int u, int v) {
    int ans = (1 << 30) - 1;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        ans &= query(1, 1, n, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    ans &= query(1, 1, n, id[u], id[v]);
    return ans;
}

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int f = queryPath(i, j);
            if (f == 0) continue;
            ans = (ans + qpow(f, f)) % MOD;
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}