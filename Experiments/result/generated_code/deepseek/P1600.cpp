#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int w[MAXN], ans[MAXN];
int n, m;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int depth[MAXN], parent[MAXN][20];

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    parent[u][0] = p;
    for (int i = 1; i < 20; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = 19; i >= 0; i--) {
        if (depth[parent[u][i]] >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    dfs(1, 0);
    for (int i = 0; i < m; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        int l = lca(s, t);
        int dist = depth[s] + depth[t] - 2 * depth[l];
        if (depth[s] - depth[l] == w[l]) {
            ans[l]++;
        }
        if (depth[t] - depth[l] == dist - w[l]) {
            ans[l]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}