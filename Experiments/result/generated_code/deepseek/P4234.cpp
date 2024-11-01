#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int find(int *parent, int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int *parent, int *rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int kruskal(int n, int m, Edge *edges, int minW, int maxW) {
    int parent[n + 1], rank[n + 1];
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int edgeCount = 0, maxEdge = INT_MIN, minEdge = INT_MAX;
    for (int i = 0; i < m; i++) {
        if (edges[i].w < minW || edges[i].w > maxW) continue;
        int x = find(parent, edges[i].u);
        int y = find(parent, edges[i].v);
        if (x != y) {
            unionSet(parent, rank, x, y);
            edgeCount++;
            if (edges[i].w > maxEdge) maxEdge = edges[i].w;
            if (edges[i].w < minEdge) minEdge = edges[i].w;
        }
        if (edgeCount == n - 1) break;
    }

    if (edgeCount == n - 1) return maxEdge - minEdge;
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

    int minDiff = INT_MAX;
    for (int i = 0; i < m; i++) {
        int diff = kruskal(n, m, edges, edges[i].w, edges[m - 1].w);
        if (diff < minDiff) minDiff = diff;
    }

    printf("%d\n", minDiff);
    return 0;
}