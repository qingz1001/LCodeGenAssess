#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    Edge edges[M];
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), (int (*)(const void *, const void *))strcmp);

    int max_time = 0;
    for (int i = 0; i < M; ++i) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_sets(edges[i].u, edges[i].v);
            max_time = edges[i].w;
        }
    }

    int components = 0;
    for (int i = 1; i <= N; ++i) {
        if (parent[i] == i) {
            components++;
        }
    }

    if (components > 1) {
        printf("-1\n");
    } else {
        printf("%d\n", max_time);
    }

    return 0;
}