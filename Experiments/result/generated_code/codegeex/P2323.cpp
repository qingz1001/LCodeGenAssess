#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w1, w2, id;
} Edge;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w1 - edgeB->w1;
}

int compareById(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->id - edgeB->id;
}

int find(int *parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent, parent[x]);
}

void unionSets(int *parent, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        if (rootX < rootY) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
        }
    }
}

int main() {
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);

    Edge edges[m - 1];
    int parent[n + 1];

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m - 1; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].w1, &edges[i].w2);
        edges[i].id = i + 1;
    }

    qsort(edges, m - 1, sizeof(Edge), compare);

    int maxCost = 0;
    int edgeCount = 0;
    int usedPrimary = 0;

    for (int i = 0; i < m - 1; i++) {
        if (find(parent, edges[i].u) != find(parent, edges[i].v)) {
            unionSets(parent, edges[i].u, edges[i].v);
            if (edges[i].w1 <= edges[i].w2) {
                maxCost = edges[i].w1;
                usedPrimary++;
            } else {
                maxCost = edges[i].w2;
            }
            edgeCount++;
            if (edgeCount == n - 1) break;
        }
    }

    if (usedPrimary < k) {
        qsort(edges, m - 1, sizeof(Edge), compareById);
        for (int i = 0; i < m - 1; i++) {
            if (find(parent, edges[i].u) != find(parent, edges[i].v)) {
                unionSets(parent, edges[i].u, edges[i].v);
                if (edges[i].w1 > edges[i].w2) {
                    maxCost = edges[i].w1;
                    usedPrimary++;
                }
                edgeCount++;
                if (edgeCount == n - 1 && usedPrimary >= k) break;
            }
        }
    }

    printf("%d\n", maxCost);

    qsort(edges, m - 1, sizeof(Edge), compareById);
    for (int i = 0; i < n - 1; i++) {
        int rootU = find(parent, edges[i].u);
        int rootV = find(parent, edges[i].v);
        if (rootU != rootV) {
            if (find(parent, edges[i].u) == rootU) {
                if (edges[i].w1 <= edges[i].w2) {
                    printf("%d 1\n", edges[i].id);
                } else {
                    printf("%d 2\n", edges[i].id);
                }
            } else {
                if (edges[i].w1 <= edges[i].w2) {
                    printf("%d 2\n", edges[i].id);
                } else {
                    printf("%d 1\n", edges[i].id);
                }
            }
        }
    }

    return 0;
}