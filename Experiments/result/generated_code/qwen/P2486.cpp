#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM << 1];
int head[MAXN], edge_cnt = 0;
int n, m;
int colors[MAXN];
int parent[MAXN];
int depth[MAXN];
int size[MAXN];
int chain_head[MAXN];
int chain_id[MAXN];
int pos_in_chain[MAXN];
int top[MAXN];

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    size[u] = 1;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        dfs(v, u, d + 1);
        size[u] += size[v];
    }
}

void decompose(int u, int t) {
    chain_head[t] = u;
    top[u] = t;
    pos_in_chain[u] = ++chain_id[0];
    int max_size = -1, max_child = -1;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent[u]) continue;
        if (size[v] > max_size) {
            max_size = size[v];
            max_child = v;
        }
    }
    if (max_child != -1) decompose(max_child, t);
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent[u] || v == max_child) continue;
        decompose(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            std::swap(u, v);
        }
        u = parent[top[u]];
    }
    return depth[u] < depth[v] ? u : v;
}

int query_color_segments(int u, int v) {
    int l = lca(u, v);
    int ans = 0;
    if (pos_in_chain[u] <= pos_in_chain[v]) {
        for (int i = pos_in_chain[u]; i <= pos_in_chain[v]; i++) {
            if (colors[chain_head[i]] != colors[chain_head[i + 1]]) ans++;
        }
    } else {
        for (int i = pos_in_chain[v]; i <= pos_in_chain[u]; i++) {
            if (colors[chain_head[i]] != colors[chain_head[i + 1]]) ans++;
        }
    }
    if (colors[u] != colors[l]) ans++;
    if (colors[v] != colors[l]) ans--;
    return ans;
}

void update_path(int u, int v, int c) {
    int l = lca(u, v);
    for (; u != l; u = parent[u]) {
        colors[u] = c;
    }
    for (; v != l; v = parent[v]) {
        colors[v] = c;
    }
    colors[l] = c;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &colors[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    memset(head, -1, sizeof(head));
    dfs(1, 0, 0);
    decompose(1, 1);
    char op;
    for (int i = 0; i < m; i++) {
        scanf(" %c", &op);
        if (op == 'C') {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            update_path(a, b, c);
        } else if (op == 'Q') {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", query_color_segments(a, b));
        }
    }
    return 0;
}