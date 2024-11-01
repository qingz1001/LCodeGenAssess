#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 100000

typedef struct {
    int u, v, t;
} Edge;

int parent[MAX_N + 1];

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

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    Edge edges[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].t);
    }

    qsort(edges, M, sizeof(Edge), (int (*)(const void *, const void *))compare);

    int max_time = -1;
    for (int i = 0; i < M; i++) {
        union_sets(edges[i].u, edges[i].v);
        int connected_components = 0;
        for (int j = 1; j <= N; j++) {
            if (parent[j] == j) {
                connected_components++;
            }
        }
        if (connected_components == 1) {
            max_time = edges[i].t;
            break;
        }
    }

    printf("%d\n", max_time);

    return 0;
}