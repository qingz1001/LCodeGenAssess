#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->w == edgeB->w) {
        if (edgeA->u == edgeB->u) {
            return edgeA->v - edgeB->v;
        }
        return edgeA->u - edgeB->u;
    }
    return edgeA->w - edgeB->w;
}

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);
    if (xRoot != yRoot) {
        if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    Edge edges[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].u--; // Convert to zero-indexed
        edges[i].v--; // Convert to zero-indexed
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int parent[n];
    int rank[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalNodes = 0;
    int totalDistance = 0;
    int i = 0;
    while (totalNodes < n) {
        Edge currentEdge = edges[i];
        int uRoot = find(parent, currentEdge.u);
        int vRoot = find(parent, currentEdge.v);
        if (uRoot != vRoot) {
            unionSets(parent, rank, uRoot, vRoot);
            totalNodes++;
            totalDistance += currentEdge.w;
        }
        i++;
    }

    printf("%d %d\n", totalNodes + 1, totalDistance);
    return 0;
}