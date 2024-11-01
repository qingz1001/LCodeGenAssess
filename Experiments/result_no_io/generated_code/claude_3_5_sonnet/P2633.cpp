#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLOGN 17

int n, m;
int weight[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
int depth[MAXN], fa[MAXN][MAXLOGN];
int dfn[MAXN], top[MAXN], son[MAXN], size[MAXN], cnt;

void addEdge(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    to[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
}

void dfs1(int u, int f) {
    depth[u] = depth[f] + 1;
    fa[u][0] = f;
    size[u] = 1;
    for (int i = 1; i < MAXLOGN; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cnt;
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u][0] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u; u = v; v = tmp;
    }
    for (int i = MAXLOGN - 1; i >= 0; i--)
        if (depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = MAXLOGN - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

int tree[MAXN * 4];

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = weight[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(node * 2, l, mid, pos, val);
    else update(node * 2 + 1, mid + 1, r, pos, val);
}

int query(int node, int l, int r, int ql, int qr, int k) {
    if (l == r) return tree[node];
    int mid = (l + r) / 2;
    int leftCount = mid - ql + 1;
    if (k <= leftCount) return query(node * 2, l, mid, ql, qr, k);
    else return query(node * 2 + 1, mid + 1, r, ql, qr, k - leftCount);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(x, y);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    build(1, 1, n);
    
    int last = 0;
    while (m--) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        u ^= last;
        int ancestor = lca(u, v);
        int result = query(1, 1, n, dfn[ancestor], dfn[u], k);
        printf("%d\n", result);
        last = result;
    }
    
    return 0;
}