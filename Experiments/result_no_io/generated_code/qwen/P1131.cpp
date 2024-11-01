#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct {
    int to, weight;
} Edge;

int n, s;
Edge edges[MAXN - 1];
int depth[MAXN], parent[MAXN];

void dfs(int node, int par, int d) {
    depth[node] = d;
    parent[node] = par;
    for (int i = 0; i < n - 1; ++i) {
        if (edges[i].to == node || edges[i].to == par) continue;
        if (edges[i].to > node) {
            dfs(edges[i].to, node, d + edges[i].weight);
        } else {
            dfs(edges[i].from, node, d + edges[i].weight);
        }
    }
}

int find_lca(int u, int v) {
    while (depth[u] > depth[v]) {
        u = parent[u];
    }
    while (depth[v] > depth[u]) {
        v = parent[v];
    }
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

int main() {
    scanf("%d", &n);
    scanf("%d", &s);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
        edges[i].from--;
        edges[i].to--;
    }

    dfs(s, -1, 0);

    int max_depth = 0;
    for (int i = 0; i < n; ++i) {
        max_depth = (max_depth > depth[i]) ? max_depth : depth[i];
    }

    int lca = find_lca(0, n - 1);
    int path_length = depth[lca] * 2;

    printf("%d\n", (path_length - max_depth) / 2);

    return 0;
}