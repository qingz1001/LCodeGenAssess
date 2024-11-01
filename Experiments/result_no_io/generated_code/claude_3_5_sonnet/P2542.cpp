#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005
#define MAXM 100005

int n, m;
int father[MAXN], size[MAXN], depth[MAXN];
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot;
int up[MAXN][16], in[MAXN], out[MAXN], timer;
int stk[MAXN], top;

void add_edge(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    to[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
}

void dfs(int u, int fa) {
    in[u] = ++timer;
    up[u][0] = fa;
    for (int i = 1; i < 16; i++)
        up[u][i] = up[up[u][i-1]][i-1];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
    out[u] = timer;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u; u = v; v = tmp;
    }
    for (int i = 15; i >= 0; i--)
        if (depth[up[u][i]] >= depth[v])
            u = up[u][i];
    if (u == v) return u;
    for (int i = 15; i >= 0; i--)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}

int find(int x) {
    return x == father[x] ? x : father[x] = find(father[x]);
}

void unite(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return;
    if (size[u] < size[v]) {
        int tmp = u; u = v; v = tmp;
    }
    father[v] = u;
    size[u] += size[v];
}

int is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        size[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        unite(u, v);
    }
    dfs(1, 0);
    
    int op, u, v;
    while (1) {
        scanf("%d", &op);
        if (op == -1) break;
        scanf("%d%d", &u, &v);
        if (op == 0) {
            unite(u, v);
        } else {
            if (find(u) != find(v)) {
                printf("%d\n", size[find(u)] + size[find(v)] - 1);
                continue;
            }
            int l = lca(u, v);
            top = 0;
            while (u != l) {
                if (!is_ancestor(u, v)) stk[++top] = u;
                u = up[u][0];
            }
            while (v != l) {
                if (!is_ancestor(v, u)) stk[++top] = v;
                v = up[v][0];
            }
            printf("%d\n", top + 1);
        }
    }
    return 0;
}