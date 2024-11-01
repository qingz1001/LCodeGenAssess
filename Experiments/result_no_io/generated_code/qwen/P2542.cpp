#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN];
int degree[MAXN];
int critical_edges[MAXN][MAXN];

void add_edge(int u, int v) {
    edges[degree[u]].to = v;
    edges[degree[u]].next = head[u];
    head[u] = degree[u]++;
}

void initialize_critical_edges(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            critical_edges[i][j] = 0;
        }
    }
}

void update_critical_edges(int n, int u, int v) {
    if (head[u] == -1 || head[v] == -1) return;
    int p1 = head[u], p2 = head[v];
    while (p1 != -1 && p2 != -1) {
        if (edges[p1].to == v) {
            critical_edges[u][v]++;
            break;
        } else if (edges[p2].to == u) {
            critical_edges[v][u]++;
            break;
        }
        p1 = edges[p1].next;
        p2 = edges[p2].next;
    }
}

int query_critical_edges(int u, int v) {
    return critical_edges[u][v];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    initialize_critical_edges(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        update_critical_edges(n, u, v);
    }

    int op;
    while (scanf("%d", &op) != EOF) {
        if (op == -1) break;
        int u, v;
        scanf("%d %d", &u, &v);
        if (op == 0) {
            update_critical_edges(n, u, v);
        } else if (op == 1) {
            printf("%d\n", query_critical_edges(u, v));
        }
    }

    return 0;
}