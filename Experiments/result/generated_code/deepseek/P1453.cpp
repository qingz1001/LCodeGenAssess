#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int p[MAXN];
int visited[MAXN];
int in_cycle[MAXN];
int cycle_start, cycle_end;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int dfs(int u, int parent) {
    visited[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        if (visited[v]) {
            cycle_start = v;
            cycle_end = u;
            return 1;
        }
        if (dfs(v, u)) {
            if (u == cycle_start) {
                in_cycle[u] = 1;
                return 0;
            }
            in_cycle[u] = 1;
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        head[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    double k;
    scanf("%lf", &k);

    dfs(0, -1);

    double total_profit = 0;
    for (int i = 0; i < n; i++) {
        if (!in_cycle[i]) {
            total_profit += p[i] * k;
        }
    }

    printf("%.1f\n", total_profit);
    return 0;
}