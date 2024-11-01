#include <stdio.h>
#include <stdlib.h>

#define MAXN 301

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int n, p;
int infected[MAXN];
int min_infected = MAXN;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int depth, int current_infected) {
    if (depth == 1) {
        infected[node] = 1;
        current_infected++;
    }

    int children_count = 0;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (infected[to] == 0) {
            children_count++;
            dfs(to, depth + 1, current_infected);
        }
    }

    if (children_count == 0) {
        if (current_infected < min_infected) {
            min_infected = current_infected;
        }
    }

    infected[node] = 0;
}

int main() {
    scanf("%d %d", &n, &p);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        infected[i] = 0;
    }

    for (int i = 0; i < p; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 1, 0);

    printf("%d\n", min_infected);

    return 0;
}