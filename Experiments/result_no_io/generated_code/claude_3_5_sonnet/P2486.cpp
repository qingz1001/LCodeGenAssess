#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLOG 17

int n, m;
int color[MAXN];
int par[MAXN][MAXLOG];
int depth[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;

struct SegTree {
    int l, r;
    int sum, lc, rc;
} tree[MAXN * 4];

void add_edge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    par[u][0] = p;
    for (int i = 1; i < MAXLOG; i++)
        par[u][i] = par[par[u][i-1]][i-1];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != p) dfs(v, u);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u; u = v; v = tmp;
    }
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (depth[par[u][i]] >= depth[v])
            u = par[u][i];
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return par[u][0];
}

void pushup(int rt) {
    tree[rt].sum = tree[rt*2].sum + tree[rt*2+1].sum - (tree[rt*2].rc == tree[rt*2+1].lc);
    tree[rt].lc = tree[rt*2].lc;
    tree[rt].rc = tree[rt*2+1].rc;
}

void build(int rt, int l, int r) {
    tree[rt].l = l;
    tree[rt].r = r;
    if (l == r) {
        tree[rt].sum = 1;
        tree[rt].lc = tree[rt].rc = color[l];
        return;
    }
    int mid = (l + r) / 2;
    build(rt*2, l, mid);
    build(rt*2+1, mid+1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int c) {
    if (tree[rt].l >= l && tree[rt].r <= r) {
        tree[rt].sum = 1;
        tree[rt].lc = tree[rt].rc = c;
        return;
    }
    int mid = (tree[rt].l + tree[rt].r) / 2;
    if (l <= mid) update(rt*2, l, r, c);
    if (r > mid) update(rt*2+1, l, r, c);
    pushup(rt);
}

int query(int rt, int l, int r) {
    if (tree[rt].l >= l && tree[rt].r <= r) return tree[rt].sum;
    int mid = (tree[rt].l + tree[rt].r) / 2;
    int res = 0;
    if (l <= mid) res += query(rt*2, l, r);
    if (r > mid) res += query(rt*2+1, l, r);
    if (l <= mid && r > mid)
        res -= (tree[rt*2].rc == tree[rt*2+1].lc);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    build(1, 1, n);
    while (m--) {
        char op[2];
        int a, b, c;
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d %d", &a, &b, &c);
            int l = lca(a, b);
            update(1, a, a, c);
            update(1, b, b, c);
            while (a != l) {
                update(1, par[a][0], a, c);
                a = par[a][0];
            }
            while (b != l) {
                update(1, par[b][0], b, c);
                b = par[b][0];
            }
        } else {
            scanf("%d %d", &a, &b);
            int l = lca(a, b);
            int res = query(1, a, a) + query(1, b, b);
            while (a != l) {
                res += query(1, par[a][0], a);
                a = par[a][0];
            }
            while (b != l) {
                res += query(1, par[b][0], b);
                b = par[b][0];
            }
            res -= query(1, l, l);
            printf("%d\n", res);
        }
    }
    return 0;
}