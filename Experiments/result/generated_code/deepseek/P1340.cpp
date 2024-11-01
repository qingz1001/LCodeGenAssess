#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200
#define MAXW 6000

typedef struct {
    int u, v, w;
} Edge;

int parent[MAXN + 1];
Edge edges[MAXW];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootY] = rootX;
    }
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main() {
    int N, W;
    scanf("%d %d", &N, &W);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int edge_count = 0;
    for (int week = 0; week < W; week++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[edge_count].u = u;
        edges[edge_count].v = v;
        edges[edge_count].w = w;
        edge_count++;

        // Kruskal's algorithm to find the minimum spanning tree
        qsort(edges, edge_count, sizeof(Edge), compare);

        int total_weight = 0;
        int components = N;
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
        }

        for (int i = 0; i < edge_count; i++) {
            int rootU = find(edges[i].u);
            int rootV = find(edges[i].v);
            if (rootU != rootV) {
                union_sets(rootU, rootV);
                total_weight += edges[i].w;
                components--;
            }
        }

        if (components == 1) {
            printf("%d\n", total_weight);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}