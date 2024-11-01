#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300005
#define MAX_M 300005
#define MOD 998244353

typedef long long ll;

int n, m;
int head[MAX_N], nxt[MAX_M * 2], to[MAX_M * 2], cnt;
int u[MAX_M], v[MAX_M], w[MAX_M];
int size[MAX_N], fa[MAX_N], dep[MAX_N], son[MAX_N], top[MAX_N];
int id[MAX_N], rid[MAX_N], tot;
ll tree[MAX_N * 4], lazy[MAX_N * 4];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f, int d) {
    size[x] = 1;
    fa[x] = f;
    dep[x] = d;
    int max_son = -1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == f) continue;
        dfs1(y, x, d + 1);
        size[x] += size[y];
        if (size[y] > max_son) {
            max_son = size[y];
            son[x] = y;
        }
    }
}

void dfs2(int x, int topf) {
    id[x] = ++tot;
    rid[tot] = x;
    top[x] = topf;
    if (!son[x]) return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}

void push_up(int rt) {
    tree[rt] = (tree[rt * 2] + tree[rt * 2 + 1]) % MOD;
}

void push_down(int rt, int l, int r) {
    if (!lazy[rt]) return;
    int mid = (l + r) >> 1;
    tree[rt * 2] = (tree[rt * 2] + lazy[rt] * (mid - l + 1)) % MOD;
    tree[rt * 2 + 1] = (tree[rt * 2 + 1] + lazy[rt] * (r - mid)) % MOD;
    lazy[rt * 2] = (lazy[rt * 2] + lazy[rt]) % MOD;
    lazy[rt * 2 + 1] = (lazy[rt * 2 + 1] + lazy[rt]) % MOD;
    lazy[rt] = 0;
}

void update(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        tree[rt] = (tree[rt] + val * (r - l + 1)) % MOD;
        lazy[rt] = (lazy[rt] + val) % MOD;
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt * 2, l, mid, L, R, val);
    if (R > mid) update(rt * 2 + 1, mid + 1, r, L, R, val);
    push_up(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(rt * 2, l, mid, L, R)) % MOD;
    if (R > mid) res = (res + query(rt * 2 + 1, mid + 1, r, L, R)) % MOD;
    return res;
}

void update_path(int x, int y, ll val) {
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

ll query_path(int x, int y) {
    ll res = 0;
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        update_path(u[i], v[i], w[i]);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ll max_val = query_path(i, j);
            ll l = 0, r = 1e9;
            while (l < r) {
                ll mid = (l + r) >> 1;
                update_path(i, j, mid + 1);
                ll new_val = query_path(i, j);
                if (new_val > max_val) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
                update_path(i, j, -(mid + 1));
            }
            ans = (ans + l) % MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}