#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 10000

typedef struct {
    int u, v, a, b;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

int compare_edges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return (e1->a * e1->b) - (e2->a * e2->b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge edges[MAXM];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }

    qsort(edges, m, sizeof(Edge), compare_edges);

    int min_product = INT_MAX;
    int min_a = 0, min_b = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) parent[j] = j;

        int total_a = 0, total_b = 0;
        int count = 0;

        for (int j = i; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int a = edges[j].a;
            int b = edges[j].b;

            if (find(u) != find(v)) {
                union_set(u, v);
                total_a += a;
                total_b += b;
                count++;
            }

            if (count == n - 1) break;
        }

        if (count == n - 1) {
            int product = total_a * total_b;
            if (product < min_product || (product == min_product && total_a < min_a)) {
                min_product = product;
                min_a = total_a;
                min_b = total_b;
            }
        }
    }

    printf("%d %d\n", min_a, min_b);

    return 0;
}