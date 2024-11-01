#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int n;
int size[MAXN], dist[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int parent) {
    size[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u);
            size[u] += size[v];
            dist[u] += dist[v] + size[v];
        }
    }
}

void dfs2(int u, int parent) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dist[v] = dist[u] - size[v] + (n - size[v]);
            dfs2(v, u);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs(1, -1);
    dfs2(1, -1);

    int min_dist = dist[1], min_node = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] < min_dist || (dist[i] == min_dist && i < min_node)) {
            min_dist = dist[i];
            min_node = i;
        }
    }

    printf("%d %d\n", min_node, min_dist);

    return 0;
}