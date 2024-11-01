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
int sorted_val[MAXN], cnt = 0;
int n, m;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int i = 1; i < MAXLOG; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + 1);
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
        if (depth[u] - (1 << i) >= depth[v]) {
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

int query(int u, int v, int k) {
    int l = lca(u, v);
    int path[MAXN * 2], path_cnt = 0;
    while (u != l) {
        path[path_cnt++] = val[u];
        u = parent[u][0];
    }
    while (v != l) {
        path[path_cnt++] = val[v];
        v = parent[v][0];
    }
    path[path_cnt++] = val[l];
    qsort(path, path_cnt, sizeof(int), cmp);
    return path[k - 1];
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        sorted_val[cnt++] = val[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs(1, 0, 0);
    int last = 0;
    for (int i = 0; i < m; i++) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u ^= last;
        last = query(u, v, k);
        printf("%d\n", last);
    }
    return 0;
}