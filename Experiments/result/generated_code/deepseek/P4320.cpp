#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int depth[MAXN], parent[MAXN][20];
bool visited[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int par, int dep) {
    visited[node] = true;
    depth[node] = dep;
    parent[node][0] = par;
    for (int i = 1; i < 20; i++) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (!visited[to]) {
            dfs(to, node, dep + 1);
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
        if (depth[u] - (1 << i) >= depth[v]) {
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
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0, 0);
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        int lca_node = lca(u, v);
        int result = depth[u] + depth[v] - 2 * depth[lca_node] + 1;
        printf("%d\n", result);
    }
    return 0;
}