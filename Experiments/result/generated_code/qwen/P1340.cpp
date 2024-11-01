#include <stdio.h>
#include <stdlib.h>

#define MAX_N 205
#define MAX_W 6005

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    parent[find(x)] = find(y);
}

int kruskal(int n, int m, Edge edges[]) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    qsort(edges, m, sizeof(Edge), [](const void *a, const void *b) {
        return ((Edge *)a)->w - ((Edge *)b)->w;
    });

    int count = 0, sum = 0;
    for (int i = 0; i < m && count < n - 1; i++) {
        Edge edge = edges[i];
        if (find(edge.u) != find(edge.v)) {
            unionSet(edge.u, edge.v);
            count++;
            sum += edge.w;
        }
    }

    if (count == n - 1) {
        return sum;
    } else {
        return -1;
    }
}

int main() {
    int n, w;
    scanf("%d %d", &n, &w);

    Edge edges[MAX_W];
    for (int i = 0; i < w; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    printf("%d\n", kruskal(n, w, edges));

    return 0;
}