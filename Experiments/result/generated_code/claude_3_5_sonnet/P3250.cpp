#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

struct Edge {
    int to, next;
} edge[MAXN * 2];

struct Query {
    int type, a, b, v, t;
} query[MAXM];

int head[MAXN], ecnt;
int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN], top[MAXN];
int dfn[MAXN], rnk[MAXN], dfs_clock;

int n, m;
int tree[MAXN * 4], lazy[MAXN * 4];

void addEdge(int u, int v) {
    edge[++ecnt] = (struct Edge){v, head[u]};
    head[u] = ecnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    sz[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++dfs_clock;
    rnk[dfs_clock] = u;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    tree[rt] = (tree[rt << 1] > tree[rt << 1 | 1]) ? tree[rt << 1] : tree[rt << 1 | 1];
}

void pushdown(int rt) {
    if (lazy[rt]) {
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        tree[rt << 1] = tree[rt << 1 | 1] = lazy[rt];
        lazy[rt] = 0;
    }
}

void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        tree[rt] = v;
        lazy[rt] = v;
        return;
    }
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt << 1, l, mid, L, R, v);
    if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R, v);
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    pushdown(rt);
    int mid = (l + r) >> 1;
    int res = -1;
    if (L <= mid) res = query(rt << 1, l, mid, L, R);
    if (R > mid) res = (res > query(rt << 1 | 1, mid + 1, r, L, R)) ? res : query(rt << 1 | 1, mid + 1, r, L, R);
    return res;
}

void modify(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        update(1, 1, n, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    update(1, 1, n, dfn[u], dfn[v], w);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d", &query[i].type);
        if (query[i].type == 0) {
            scanf("%d%d%d", &query[i].a, &query[i].b, &query[i].v);
        } else if (query[i].type == 1) {
            scanf("%d", &query[i].t);
        } else {
            scanf("%d", &query[i].a);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        if (query[i].type == 0) {
            modify(query[i].a, query[i].b, query[i].v);
        } else if (query[i].type == 1) {
            modify(query[query[i].t].a, query[query[i].t].b, -1);
        } else {
            int res = query(1, 1, n, 1, n);
            printf("%d\n", res);
        }
    }
    
    return 0;
}