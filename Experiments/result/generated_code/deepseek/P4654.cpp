#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int n, t, m;
int depth[MAXN], parent[MAXN], subtree_size[MAXN];
bool blocked[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int par) {
    parent[node] = par;
    depth[node] = depth[par] + 1;
    subtree_size[node] = 1;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != par) {
            dfs(to, node);
            subtree_size[node] += subtree_size[to];
        }
    }
}

int find_lca(int u, int v) {
    while (u != v) {
        if (depth[u] > depth[v]) {
            u = parent[u];
        } else {
            v = parent[v];
        }
    }
    return u;
}

int min_operations(int node, int par) {
    int operations = 0;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != par && !blocked[to]) {
            operations += min_operations(to, node);
        }
    }
    if (node != t) {
        operations++;
    }
    return operations;
}

int main() {
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs(t, 0);

    int lca = find_lca(t, m);
    int current = m;
    while (current != lca) {
        blocked[current] = true;
        current = parent[current];
    }

    printf("%d\n", min_operations(t, 0));

    return 0;
}