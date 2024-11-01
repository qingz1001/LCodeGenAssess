#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define MAXM 10005

typedef struct {
    int u, v;
    int a, b;
    int index;
} Edge;

int parent[MAXN];
Edge edges[MAXM];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int compare(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    long long pa = (long long)ea->a * eb->b - (long long)ea->b * eb->a;
    long long pb = (long long)eb->a * ea->b - (long long)eb->b * ea->a;
    if (pa == pb) return ea->index - eb->index;
    return pa > pb ? 1 : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
        edges[i].index = i;
    }

    for (int i = 0; i < n; i++) parent[i] = i;

    qsort(edges, m, sizeof(Edge), compare);

    int sum_a = 0, sum_b = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            union_set(u, v);
            sum_a += edges[i].a;
            sum_b += edges[i].b;
        }
    }

    printf("%d %d\n", sum_a, sum_b);

    return 0;
}