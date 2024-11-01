#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

int n, m;
ll values[MAXN];
int parent[MAXN], depth[MAXN], size[MAXN];
int heavy_child[MAXN], subtree_size[MAXN];
int euler_tour[MAXN * 2], tour_index = 0;
int in_tour[MAXN], out_tour[MAXN];

void dfs(int node, int par, int dep) {
    parent[node] = par;
    depth[node] = dep;
    size[node] = 1;
    heavy_child[node] = -1;
    for (int i = head[node]; ~i; i = edges[i].next) {
        int to = edges[i].to;
        if (to == par) continue;
        dfs(to, node, dep + 1);
        size[node] += size[to];
        if (heavy_child[node] == -1 || size[to] > size[heavy_child[node]]) {
            heavy_child[node] = to;
        }
    }
}

void euler_tour_dfs(int node, int par) {
    in_tour[node] = tour_index++;
    euler_tour[tour_index++] = node;
    if (heavy_child[node] != -1) {
        euler_tour_dfs(heavy_child[node], node);
    }
    for (int i = head[node]; ~i; i = edges[i].next) {
        int to = edges[i].to;
        if (to == par || to == heavy_child[node]) continue;
        euler_tour_dfs(to, node);
    }
    out_tour[node] = tour_index++;
    euler_tour[tour_index++] = node;
}

int lca(int u, int v) {
    while (in_tour[u] > in_tour[v]) u = parent[u];
    while (in_tour[v] > in_tour[u]) v = parent[v];
    return u;
}

int query_kth_smallest(int u, int v, int k) {
    int l = lca(u, v);
    int left_count = in_tour[u] - in_tour[l] + 1;
    int right_count = in_tour[v] - in_tour[l] + 1;
    if (k <= left_count) {
        return query_tree(in_tour[l], in_tour[u]);
    } else {
        return query_tree(in_tour[l] + left_count, in_tour[v]);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &values[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }
    dfs(1, -1, 0);
    euler_tour_dfs(1, -1);

    // Build segment tree and other necessary data structures here

    for (int i = 1; i <= m; i++) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        printf("%lld\n", query_kth_smallest(u, v, k));
    }

    return 0;
}