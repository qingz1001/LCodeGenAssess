#include <stdio.h>
#include <stdlib.h>

#define MAXN 366667

int n;
int tree[MAXN][2];
int depth[MAXN];
int depth_prime[MAXN];

void dfs(int node, int parent, int d) {
    depth[node] = d;
    tree[node][0] = parent;
    for (int i = 1; i < 20; i++) {
        tree[node][i] = tree[tree[node][i - 1]][i - 1];
    }
    for (int i = 0; i < 2; i++) {
        if (tree[node][i] != -1) {
            dfs(tree[node][i], node, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        return lca(v, u);
    }
    for (int i = 19; i >= 0; i--) {
        if ((depth[v] - depth[u]) & (1 << i)) {
            v = tree[v][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (tree[u][i] != tree[v][i]) {
            u = tree[u][i];
            v = tree[v][i];
        }
    }
    return tree[u][0];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            tree[i][j] = -1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        tree[x][0] = y;
        tree[y][0] = x;
    }
    dfs(1, -1, 0);

    for (int i = 1; i <= n; i++) {
        depth_prime[i] = -1;
    }
    for (int i = n; i < 2 * n - 1; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        tree[x][0] = y;
        tree[y][0] = x;
    }
    dfs(1, -1, 0);

    long long max_distance = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int lca_node = lca(i, j);
            int dist = depth[i] + depth[j] - (depth[lca_node] + depth_prime[lca_node]);
            if (dist > max_distance) {
                max_distance = dist;
            }
        }
    }

    printf("%lld\n", max_distance);

    return 0;
}