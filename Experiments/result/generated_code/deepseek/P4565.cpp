#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 366666
#define MAXM (2 * MAXN)

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], depth[MAXN], depth2[MAXN], parent[MAXN], edge_count = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int p, int d, int* depth) {
    depth[u] = d;
    parent[u] = p;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + edges[i].weight, depth);
        }
    }
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

    dfs(1, -1, 0, depth);

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

    dfs(1, -1, 0, depth2);

    int max_dist = INT_MIN;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int lca_depth = 0;
            int lca_depth2 = 0;
            int x = i, y = j;
            while (x != y) {
                if (depth[x] > depth[y]) {
                    x = parent[x];
                } else {
                    y = parent[y];
                }
            }
            lca_depth = depth[x];

            x = i, y = j;
            while (x != y) {
                if (depth2[x] > depth2[y]) {
                    x = parent[x];
                } else {
                    y = parent[y];
                }
            }
            lca_depth2 = depth2[x];

            int dist = depth[i] + depth[j] - (lca_depth + lca_depth2);
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }

    printf("%d\n", max_dist);

    return 0;
}