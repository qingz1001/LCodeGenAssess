#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001
#define MAXM 200001

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i)
        parent[i] = i;

    Edge edges[MAXM];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    int maxWeight = 0, minWeight = INT_MAX;
    int edgeCount = 0;

    for (int i = 0; i < m && edgeCount < n - 1; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            union_set(u, v);
            maxWeight = w;
            if (minWeight == INT_MAX) {
                minWeight = w;
            }
            edgeCount++;
        }
    }

    printf("%d\n", maxWeight - minWeight);

    return 0;
}