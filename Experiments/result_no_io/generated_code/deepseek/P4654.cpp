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
int depth[MAXN], parent[MAXN], clean_count[MAXN], dirty_count[MAXN];
bool blocked[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u);
        }
    }
}

void calculate_counts(int u, int p) {
    clean_count[u] = 0;
    dirty_count[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p && !blocked[v]) {
            calculate_counts(v, u);
            clean_count[u] += clean_count[v] + 1;
            dirty_count[u] += dirty_count[v];
        }
    }
    if (u != t && u != m) {
        dirty_count[u]++;
    }
}

int main() {
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs(t, 0);

    int current = m;
    int operations = 0;
    while (current != t) {
        blocked[current] = true;
        current = parent[current];
        operations++;
    }

    calculate_counts(t, 0);

    int total_operations = operations;
    for (int i = 1; i <= n; i++) {
        if (i != t && i != m) {
            total_operations += dirty_count[i];
        }
    }

    printf("%d\n", total_operations);

    return 0;
}