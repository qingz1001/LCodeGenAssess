#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000
#define MAXM 10000

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXN + 1];
Edge edges[MAXM];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), compare);

    int max_edge = 0;
    int edge_count = 0;

    for (int i = 0; i < M; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            union_set(u, v);
            max_edge = w;
            edge_count++;
            if (edge_count == N - 1)
                break;
        }
    }

    printf("%d\n", max_edge);

    return 0;
}