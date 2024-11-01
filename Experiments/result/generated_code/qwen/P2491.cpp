#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005

typedef struct {
    int to, len;
} Edge;

int n, s;
Edge edges[MAXN];
int degree[MAXN];
int parent[MAXN], depth[MAXN];

void add_edge(int u, int v, int w) {
    edges[n].to = v;
    edges[n].len = w;
    degree[u]++;
    edges[++n].to = u;
    edges[n].len = w;
}

void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (int i = 0; i < degree[u]; i++) {
        int v = edges[i * 2 + 1].to;
        if (v != p) {
            dfs(v, u, d + edges[i * 2 + 1].len);
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

int get_max_distance(int u, int v) {
    int lca = find_lca(u, v);
    int dist_u = depth[u] - depth[lca];
    int dist_v = depth[v] - depth[lca];
    int max_dist = INT_MIN;
    for (int i = 0; i < degree[u]; i++) {
        int v = edges[i * 2 + 1].to;
        if (v != parent[u]) {
            max_dist = fmax(max_dist, dist_u + get_max_distance(v, u));
        }
    }
    for (int i = 0; i < degree[v]; i++) {
        int u = edges[i * 2].to;
        if (u != parent[v]) {
            max_dist = fmax(max_dist, dist_v + get_max_distance(u, v));
        }
    }
    return max_dist;
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    dfs(1, -1, 0);
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int dist = get_max_distance(i, j);
            if (dist <= s) {
                ans = fmin(ans, dist);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}