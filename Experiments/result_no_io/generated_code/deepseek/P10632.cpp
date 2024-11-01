#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 30000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[2 * MAXN];
int head[MAXN];
int size[MAXN];
int n;

void add_edge(int u, int v, int idx) {
    edges[idx].to = v;
    edges[idx].next = head[u];
    head[u] = idx;
}

void dfs(int u, int parent) {
    size[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

double expected_time(int u, int parent) {
    double time = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            time += expected_time(v, u);
        }
    }
    return time + size[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    int edge_count = 0;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b, edge_count++);
        add_edge(b, a, edge_count++);
    }

    dfs(0, -1);
    double result = expected_time(0, -1);
    printf("%.4f\n", result / n);

    return 0;
}