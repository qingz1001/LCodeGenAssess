#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef struct Edge {
    int to, next;
} Edge;

int n, m;
int head[MAXN], cnt;
Edge edges[MAXN * 2];
int color[MAXN];
int depth[MAXN], fa[MAXN][20], top[MAXN], son[MAXN], size[MAXN];

void addEdge(int u, int v) {
    edges[++cnt] = (Edge){v, head[u]};
    head[u] = cnt;
}

void dfs1(int u, int f) {
    depth[u] = depth[f] + 1;
    fa[u][0] = f;
    size[u] = 1;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa[u][0] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    for (int i = 19; i >= 0; i--)
        if (depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

int query(int u, int v) {
    int ans = 0, last = -1;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        if (color[u] != last) ans++;
        last = color[top[u]];
        u = fa[top[u]][0];
    }
    if (depth[u] > depth[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    if (color[v] != last) ans++;
    return ans;
}

void change(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        for (int i = u; i >= top[u]; i = fa[i][0])
            color[i] = c;
        u = fa[top[u]][0];
    }
    if (depth[u] > depth[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    for (int i = u; i <= v; i = son[i])
        color[i] = c;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    for (int i = 0; i < m; i++) {
        char op[2];
        int a, b, c;
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query(a, b));
        } else {
            scanf("%d %d %d", &a, &b, &c);
            change(a, b, c);
        }
    }
    
    return 0;
}