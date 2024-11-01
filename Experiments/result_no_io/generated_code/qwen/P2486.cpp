#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int color[MAXN];
int parent[MAXN];
int depth[MAXN];

void add_edge(int from, int to) {
    edges[edge_count].to = to;
    edges[edge_count].next = head[from];
    head[from] = edge_count++;
}

void dfs(int node, int p, int d) {
    parent[node] = p;
    depth[node] = d;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == p) continue;
        color[to] = color[node];
        dfs(to, node, d + 1);
    }
}

int find_lca(int a, int b) {
    if (depth[a] > depth[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    int diff = depth[b] - depth[a];
    while (diff > 0) {
        int step = __builtin_clz(diff) ^ 31;
        b = parent[b][step];
        diff -= 1 << step;
    }
    if (a == b) return a;
    for (int i = 30; i >= 0; i--) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 0; i < n; i++) head[i] = -1;
    dfs(1, -1, 0);

    int q;
    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'C') {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            int lca = find_lca(a, b);
            int path_length = depth[a] + depth[b] - 2 * depth[lca];
            printf("%d\n", path_length + 1);
        } else if (op == 'Q') {
            int a, b;
            scanf("%d %d", &a, &b);
            int lca = find_lca(a, b);
            int path_length = depth[a] + depth[b] - 2 * depth[lca];
            printf("%d\n", path_length + 1);
        }
    }

    return 0;
}