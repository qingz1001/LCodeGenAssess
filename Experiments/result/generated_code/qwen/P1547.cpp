#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_M 10000

typedef struct {
    int a, b, l;
} Edge;

int parent[MAX_N + 1];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->l - e2->l;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++)
        parent[i] = i;

    Edge edges[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    qsort(edges, M, sizeof(Edge), compare);

    int max_length = 0;
    for (int i = 0; i < M; i++) {
        if (find(edges[i].a) != find(edges[i].b)) {
            union_sets(edges[i].a, edges[i].b);
            max_length = edges[i].l;
        }
    }

    printf("%d\n", max_length);

    return 0;
}