#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define MAXM 10010

typedef struct {
    int u, v;
    int a, b;
    int cost;
} Edge;

Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->cost - edgeB->cost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
        edges[i].cost = edges[i].a + edges[i].b;
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int sum_a = 0, sum_b = 0;
    int count = 0;

    for (int i = 0; i < m && count < n - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int a = edges[i].a;
        int b = edges[i].b;

        if (find(u) != find(v)) {
            union_sets(u, v);
            sum_a += a;
            sum_b += b;
            ++count;
        }
    }

    printf("%d %d\n", sum_a, sum_b);

    return 0;
}