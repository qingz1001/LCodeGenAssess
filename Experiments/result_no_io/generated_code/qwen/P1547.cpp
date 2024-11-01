#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000
#define MAXM 10000

typedef struct {
    int a, b, l;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSets(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->l - ((Edge *)b)->l;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i <= N; ++i)
        parent[i] = i;

    Edge edges[MAXM];
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    qsort(edges, M, sizeof(Edge), compare);

    int maxEdgeLength = 0;
    for (int i = 0; i < M; ++i) {
        if (find(edges[i].a) != find(edges[i].b)) {
            unionSets(edges[i].a, edges[i].b);
            maxEdgeLength = edges[i].l;
        }
    }

    printf("%d\n", maxEdgeLength);

    return 0;
}