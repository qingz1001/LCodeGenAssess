#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005
#define MAXLOG 20

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt = 0;
int depth[MAXN], parent[MAXN][MAXLOG], val[MAXN];
int n, m, last = 0;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    parent[u][0] = p;
    for (int i = 1; i < MAXLOG; i++) {
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
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (depth[parent[u][i]] >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs(1, 0);
    for (int i = 0; i < m; i++) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u ^= last;
        int lca_node = lca(u, v);
        int path_length = depth[u] + depth[v] - 2 * depth[lca_node] + 1;
        int path[path_length];
        int idx = 0;
        while (u != lca_node) {
            path[idx++] = val[u];
            u = parent[u][0];
        }
        while (v != lca_node) {
            path[idx++] = val[v];
            v = parent[v][0];
        }
        path[idx++] = val[lca_node];
        qsort(path, path_length, sizeof(int), cmp);
        last = path[k - 1];
        printf("%d\n", last);
    }
    return 0;
}