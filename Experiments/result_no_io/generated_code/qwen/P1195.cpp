#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1005
#define MAX_M 10005
#define MAX_K 11

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX_N];
int rank[MAX_N];

void make_set(int x) {
    parent[x] = x;
    rank[x] = 0;
}

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find_set(x), py = find_set(y);
    if (px == py) return;
    if (rank[px] > rank[py])
        parent[py] = px;
    else if (rank[px] < rank[py])
        parent[px] = py;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

int kruskal(int n, int m, int k, Edge edges[]) {
    for (int i = 1; i <= n; i++)
        make_set(i);

    qsort(edges, m, sizeof(Edge), [](const void *a, const void *b) {
        return ((Edge *)a)->w - ((Edge *)b)->w;
    });

    int count = 0, cost = 0;
    for (int i = 0; i < m && count < n - k + 1; i++) {
        Edge e = edges[i];
        if (find_set(e.u) != find_set(e.v)) {
            union_sets(e.u, e.v);
            count++;
            cost += e.w;
        }
    }

    if (count < n - k + 1)
        return -1;
    return cost;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Edge edges[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int result = kruskal(n, m, k, edges);
    if (result == -1)
        printf("No Answer\n");
    else
        printf("%d\n", result);

    return 0;
}