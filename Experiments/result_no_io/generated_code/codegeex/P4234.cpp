#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 200005

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int parent[MAXN];
Edge edges[MAXM];

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    int minDifference = INT_MAX;
    for (int i = 0; i <= m - n + 1; i++) {
        for (int j = 0; j < n; j++) {
            parent[j] = j;
        }

        int maxEdge = 0;
        int minEdge = edges[i].w;
        int edgesUsed = 0;

        for (int j = i; j < m && edgesUsed < n - 1; j++) {
            int u = edges[j].u - 1;
            int v = edges[j].v - 1;
            int w = edges[j].w;

            if (find(u) != find(v)) {
                unionSets(u, v);
                maxEdge = w;
                edgesUsed++;
            }
        }

        if (edgesUsed == n - 1) {
            minDifference = fmin(minDifference, maxEdge - minEdge);
        }
    }

    printf("%d\n", minDifference);
    return 0;
}