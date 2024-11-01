#include <stdio.h>
#include <stdlib.h>

#define MAXN 366666
#define INF 2017011328

typedef struct {
    int to, next, w;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;
int depth[MAXN], depth_prime[MAXN];
int parent[MAXN][20];

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    edges[edge_count].w = w;
    head[u] = edge_count++;
}

void dfs(int u, int p, int d, int d_prime) {
    depth[u] = d;
    depth_prime[u] = d_prime;
    parent[u][0] = p;
    for (int i = 1; i <= 19; i++) {
        if (parent[u][i - 1] != -1) {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        } else {
            parent[u][i] = -1;
        }
    }
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to;
        if (v == p) continue;
        dfs(v, u, d + edges[e].w, d_prime);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        int t = u;
        u = v;
        v = t;
    }
    int k = depth[v] - depth[u];
    for (int i = 19; i >= 0; i--) {
        if (k & (1 << i)) {
            v = parent[v][i];
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
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        add_edge(x, y, w);
        add_edge(y, x, w);
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        add_edge(x, y, w);
        add_edge(y, x, w);
    }
    memset(head, -1, sizeof(head));
    memset(parent, -1, sizeof(parent));
    dfs(1, -1, 0, 0);
    int max_distance = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int u = i, v = j;
            int lca_u = lca(u, v);
            int lca_v = lca(u, v);
            int distance = depth[u] + depth[v] - (depth[lca_u] + depth_prime[lca_v]);
            if (distance > max_distance) {
                max_distance = distance;
            }
        }
    }
    printf("%d\n", max_distance);
    return 0;
}