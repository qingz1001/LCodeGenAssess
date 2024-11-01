#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MOD 64123

int n, k, W;
int d[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], tot;
int sz[MAX_N], son[MAX_N], dep[MAX_N], fa[MAX_N], top[MAX_N];
int id[MAX_N], rid[MAX_N], cnt;
int sum[MAX_N * 4], add[MAX_N * 4];

void addEdge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int u, int f) {
    sz[u] = 1;
    dep[u] = dep[f] + 1;
    fa[u] = f;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    id[u] = ++cnt;
    rid[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    sum[rt] = (sum[rt * 2] + sum[rt * 2 + 1]) % MOD;
}

void pushdown(int rt, int l, int r) {
    if (add[rt] == 0) return;
    int mid = (l + r) >> 1;
    sum[rt * 2] = (sum[rt * 2] + (mid - l + 1) * add[rt]) % MOD;
    sum[rt * 2 + 1] = (sum[rt * 2 + 1] + (r - mid) * add[rt]) % MOD;
    add[rt * 2] = (add[rt * 2] + add[rt]) % MOD;
    add[rt * 2 + 1] = (add[rt * 2 + 1] + add[rt]) % MOD;
    add[rt] = 0;
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        sum[rt] = (sum[rt] + (r - l + 1) * val) % MOD;
        add[rt] = (add[rt] + val) % MOD;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt * 2, l, mid, L, R, val);
    if (R > mid) update(rt * 2 + 1, mid + 1, r, L, R, val);
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res = (res + query(rt * 2, l, mid, L, R)) % MOD;
    if (R > mid) res = (res + query(rt * 2 + 1, mid + 1, r, L, R)) % MOD;
    return res;
}

void updatePath(int x, int y, int val) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            int temp = x;
            x = y;
            y = temp;
        }
        update(1, 1, n, id[top[x]], id[x], val);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    update(1, 1, n, id[x], id[y], val);
}

int queryPath(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            int temp = x;
            x = y;
            y = temp;
        }
        res = (res + query(1, 1, n, id[top[x]], id[x])) % MOD;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    res = (res + query(1, 1, n, id[x], id[y])) % MOD;
    return res;
}

int main() {
    scanf("%d %d %d", &n, &k, &W);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = rid[i];
        updatePath(1, x, 1);
        ans = (ans + 1LL * d[x] * queryPath(1, x) % MOD) % MOD;
        if (i >= k) {
            int y = rid[i - k + 1];
            updatePath(1, y, MOD - 1);
        }
    }

    printf("%lld\n", ans);
    return 0;
}