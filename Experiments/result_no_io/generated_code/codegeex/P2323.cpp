#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    int cost1;
    int cost2;
    int index;
} Edge;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->cost1 - edgeB->cost1;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);

    if (xRoot != yRoot) {
        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
}

int main() {
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);

    Edge edges[m - 1];
    for (int i = 0; i < m - 1; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost1, &edges[i].cost2);
        edges[i].index = i + 1;
    }

    qsort(edges, m - 1, sizeof(Edge), compare);

    int parent[n + 1];
    int rank[n + 1];
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int numPrimary = 0;
    int maxCost = 0;
    int edgeCount = 0;
    int result[n - 1][2];

    for (int i = 0; i < m - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int cost1 = edges[i].cost1;
        int cost2 = edges[i].cost2;
        int index = edges[i].index;

        if (find(parent, u) != find(parent, v)) {
            if (numPrimary < k) {
                unionSets(parent, rank, u, v);
                result[edgeCount][0] = index;
                result[edgeCount][1] = 1;
                numPrimary++;
                maxCost = cost1;
            } else if (cost1 < cost2) {
                unionSets(parent, rank, u, v);
                result[edgeCount][0] = index;
                result[edgeCount][1] = 1;
                maxCost = cost1;
            } else {
                unionSets(parent, rank, u, v);
                result[edgeCount][0] = index;
                result[edgeCount][1] = 2;
                maxCost = cost2;
            }
            edgeCount++;
            if (edgeCount == n - 1)
                break;
        }
    }

    printf("%d\n", maxCost);
    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }

    return 0;
}