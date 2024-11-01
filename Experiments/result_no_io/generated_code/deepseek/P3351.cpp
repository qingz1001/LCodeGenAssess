#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct {
    int v;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
bool visited[MAXN];
int parent[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].v = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (!visited[v]) {
            dfs(v, u);
        }
    }
}

bool is_biconnected(int n) {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        visited[i] = false;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, -1);

    if (!is_biconnected(n)) {
        printf("0\n");
        return 0;
    }

    int count = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (parent[u] != v && parent[v] != u) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}