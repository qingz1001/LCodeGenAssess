#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 10000

typedef struct {
    int u, v, a, b;
} Edge;

Edge edges[MAXM];
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

int compare_a(const void *a, const void *b) {
    return ((Edge *)a)->a - ((Edge *)b)->a;
}

int compare_b(const void *a, const void *b) {
    return ((Edge *)a)->b - ((Edge *)b)->b;
}

int compare_ab(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return (e1->a * e1->b) - (e2->a * e2->b);
}

void kruskal(int n, int m, int *sum_a, int *sum_b) {
    for (int i = 0; i < n; i++) parent[i] = i;
    *sum_a = *sum_b = 0;
    int count = 0;

    for (int i = 0; i < m && count < n - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        int a = edges[i].a, b = edges[i].b;
        if (find(u) != find(v)) {
            union_set(u, v);
            *sum_a += a;
            *sum_b += b;
            count++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }

    qsort(edges, m, sizeof(Edge), compare_a);
    int min_a = INT_MAX, min_b = INT_MAX;
    int sum_a, sum_b;
    kruskal(n, m, &sum_a, &sum_b);
    if (sum_a * sum_b < min_a * min_b) {
        min_a = sum_a;
        min_b = sum_b;
    }

    qsort(edges, m, sizeof(Edge), compare_b);
    kruskal(n, m, &sum_a, &sum_b);
    if (sum_a * sum_b < min_a * min_b) {
        min_a = sum_a;
        min_b = sum_b;
    }

    qsort(edges, m, sizeof(Edge), compare_ab);
    kruskal(n, m, &sum_a, &sum_b);
    if (sum_a * sum_b < min_a * min_b) {
        min_a = sum_a;
        min_b = sum_b;
    }

    printf("%d %d\n", min_a, min_b);
    return 0;
}