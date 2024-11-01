#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

struct Edge {
    int to, next;
} edge[MAXN * 2];

struct Request {
    int a, b, t, v;
} req[MAXM];

int head[MAXN], tot;
int fa[MAXN][17], dep[MAXN];
int n, m, reqCnt;
int seg[MAXN * 4], lazy[MAXN * 4];
int in[MAXN], out[MAXN], dfsn;

void addEdge(int u, int v) {
    edge[++tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}

void dfs(int u, int f) {
    in[u] = ++dfsn;
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for (int i = 1; i < 17; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v != f) dfs(v, u);
    }
    out[u] = dfsn;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int t = u; u = v; v = t;
    }
    for (int i = 16; i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 16; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

void pushUp(int rt) {
    seg[rt] = seg[rt*2] > seg[rt*2+1] ? seg[rt*2] : seg[rt*2+1];
}

void pushDown(int rt) {
    if (lazy[rt]) {
        seg[rt*2] = lazy[rt*2] = lazy[rt];
        seg[rt*2+1] = lazy[rt*2+1] = lazy[rt];
        lazy[rt] = 0;
    }
}

void update(int L, int R, int C, int l, int r, int rt) {
    if (L <= l && r <= R) {
        seg[rt] = lazy[rt] = C;
        return;
    }
    pushDown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) update(L, R, C, l, mid, rt*2);
    if (R > mid) update(L, R, C, mid+1, r, rt*2+1);
    pushUp(rt);
}

int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return seg[rt];
    pushDown(rt);
    int mid = (l + r) >> 1, ans = 0;
    if (L <= mid) ans = query(L, R, l, mid, rt*2);
    if (R > mid) ans = ans > query(L, R, mid+1, r, rt*2+1) ? ans : query(L, R, mid+1, r, rt*2+1);
    return ans;
}

void add(int u, int v, int t, int val) {
    int l = lca(u, v);
    update(in[u], in[u], val, 1, n, 1);
    update(in[v], in[v], val, 1, n, 1);
    update(in[l], in[l], -val, 1, n, 1);
    if (fa[l][0]) update(in[fa[l][0]], in[fa[l][0]], -val, 1, n, 1);
    req[++reqCnt] = (struct Request){u, v, t, val};
}

void del(int id) {
    int u = req[id].a, v = req[id].b, val = req[id].v;
    int l = lca(u, v);
    update(in[u], in[u], -val, 1, n, 1);
    update(in[v], in[v], -val, 1, n, 1);
    update(in[l], in[l], val, 1, n, 1);
    if (fa[l][0]) update(in[fa[l][0]], in[fa[l][0]], val, 1, n, 1);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    
    for (int i = 1; i <= m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int a, b, v;
            scanf("%d%d%d", &a, &b, &v);
            add(a, b, i, v);
        } else if (type == 1) {
            int t;
            scanf("%d", &t);
            del(t);
        } else {
            int x;
            scanf("%d", &x);
            int ans = query(in[x], out[x], 1, n, 1);
            printf("%d\n", ans ? ans : -1);
        }
    }
    return 0;
}