#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 366666

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], depth[MAXN], depth_prime[MAXN], parent[MAXN], edge_count = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int parent_node, int d, int *depth) {
    depth[node] = d;
    parent[node] = parent_node;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != parent_node) {
            dfs(to, node, d + edges[i].weight, depth);
        }
    }
}

int lca(int u, int v, int *depth) {
    while (u != v) {
        if (depth[u] > depth[v]) {
            u = parent[u];
        } else {
            v = parent[v];
        }
    }
    return u;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (int i = 1; i < n; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        add_edge(x, y, v);
        add_edge(y, x, v);
    }

    dfs(1, 0, 0, depth);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edge_count = 0;

    for (int i = 1; i < n; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        add_edge(x, y, v);
        add_edge(y, x, v);
    }

    dfs(1, 0, 0, depth_prime);

    int max_distance = INT_MIN;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int lca_t = lca(i, j, depth);
            int lca_t_prime = lca(i, j, depth_prime);
            int distance = depth[i] + depth[j] - (depth[lca_t] + depth_prime[lca_t_prime]);
            if (distance > max_distance) {
                max_distance = distance;
            }
        }
    }

    printf("%d\n", max_distance);

    return 0;
}