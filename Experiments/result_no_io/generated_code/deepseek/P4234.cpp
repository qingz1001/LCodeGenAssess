#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int kruskal(Edge edges[], int n, int m, int start, int end) {
    int parent[n + 1], rank[n + 1];
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int max_w = INT_MIN, min_w = INT_MAX;
    int num_edges = 0;

    for (int i = start; i < end; i++) {
        int x = find(parent, edges[i].u);
        int y = find(parent, edges[i].v);

        if (x != y) {
            unionSet(parent, rank, x, y);
            num_edges++;
            if (edges[i].w > max_w) max_w = edges[i].w;
            if (edges[i].w < min_w) min_w = edges[i].w;
        }

        if (num_edges == n - 1) break;
    }

    if (num_edges == n - 1)
        return max_w - min_w;
    else
        return INT_MAX;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge edges[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int min_diff = INT_MAX;
    for (int i = 0; i < m; i++) {
        int diff = kruskal(edges, n, m, i, m);
        if (diff < min_diff) min_diff = diff;
    }

    printf("%d\n", min_diff);

    return 0;
}