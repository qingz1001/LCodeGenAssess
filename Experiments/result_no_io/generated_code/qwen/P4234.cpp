#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 200005

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXN];
Edge edges[MAXM];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int min_cost = 0, max_cost = 0;
    int edge_count = 0;

    for (int i = 0; i < m && edge_count < n - 1; ++i) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_sets(edges[i].u, edges[i].v);
            if (edge_count == 0) {
                min_cost = edges[i].w;
            }
            max_cost = edges[i].w;
            ++edge_count;
        }
    }

    printf("%d\n", max_cost - min_cost);

    return 0;
}