#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 1048576
#define MOD 10007

int n, m, q;
int v[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;
int size[MAXN], son[MAXN], top[MAXN], fa[MAXN], dep[MAXN];
int id[MAXN], rid[MAXN], cnt;
int tree[MAXN * 4], lazy[MAXN * 4];
int f[MAXM][20], g[MAXM];

void add_edge(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}

void dfs1(int u, int father) {
    size[u] = 1; fa[u] = father; dep[u] = dep[father] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == father) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    id[u] = ++cnt; rid[cnt] = u; top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    tree[rt] = tree[rt * 2] ^ tree[rt * 2 + 1];
}

void pushdown(int rt, int l, int r) {
    if (!lazy[rt]) return;
    int mid = (l + r) >> 1;
    lazy[rt * 2] ^= lazy[rt];
    lazy[rt * 2 + 1] ^= lazy[rt];
    tree[rt * 2] ^= lazy[rt] * (mid - l + 1);
    tree[rt * 2 + 1] ^= lazy[rt] * (r - mid);
    lazy[rt] = 0;
}

void build(int rt, int l, int r) {
    if (l == r) {
        tree[rt] = v[rid[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        lazy[rt] ^= val;
        tree[rt] ^= val * (r - l + 1);
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt * 2, l, mid, L, R, val);
    if (R > mid) update(rt * 2 + 1, mid + 1, r, L, R, val);
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res ^= query(rt * 2, l, mid, L, R);
    if (R > mid) res ^= query(rt * 2 + 1, mid + 1, r, L, R);
    return res;
}

void modify(int x, int y) {
    update(1, 1, n, id[x], id[x], v[x] ^ y);
    v[x] = y;
}

int getsum(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            int t = x; x = y; y = t;
        }
        res ^= query(1, 1, n, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        int t = x; x = y; y = t;
    }
    res ^= query(1, 1, n, id[x], id[y]);
    return res;
}

void init() {
    for (int i = 0; i < m; i++) {
        f[i][0] = 1;
        for (int j = 1; j < 20; j++) {
            f[i][j] = f[i][j - 1] * 2 % MOD;
        }
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    init();
    scanf("%d", &q);
    while (q--) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'C') {
            int x, y;
            scanf("%d%d", &x, &y);
            modify(x, y);
        } else {
            int k;
            scanf("%d", &k);
            memset(g, 0, sizeof(g));
            g[0] = 1;
            for (int i = 1; i <= n; i++) {
                int sum = getsum(1, i);
                for (int j = 0; j < m; j++) {
                    g[j ^ sum] = (g[j ^ sum] + g[j]) % MOD;
                }
            }
            printf("%d\n", g[k]);
        }
    }
    return 0;
}