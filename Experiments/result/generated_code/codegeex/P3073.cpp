#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 501
#define MAXM (MAXN * MAXN)

typedef struct {
    int x, y, cost;
} Edge;

int n;
int grid[MAXN][MAXN];
Edge edges[MAXM * 4];
int edgeCount = 0;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->cost - edgeB->cost;
}

void addEdge(int x1, int y1, int x2, int y2) {
    edges[edgeCount++] = (Edge){x1, y1, abs(grid[x1][y1] - grid[x2][y2])};
    edges[edgeCount++] = (Edge){x2, y2, abs(grid[x1][y1] - grid[x2][y2])};
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
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) addEdge(i, j, i - 1, j);
            if (j > 0) addEdge(i, j, i, j - 1);
            if (i < n - 1) addEdge(i, j, i + 1, j);
            if (j < n - 1) addEdge(i, j, i, j + 1);
        }
    }

    qsort(edges, edgeCount, sizeof(Edge), compare);

    int parent[MAXM];
    int rank[MAXM];
    for (int i = 0; i < n * n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstCost = 0;
    int mstSize = 0;
    for (int i = 0; i < edgeCount; i++) {
        Edge edge = edges[i];
        int x = edge.x;
        int y = edge.y;
        int cost = edge.cost;

        if (find(parent, x) != find(parent, y)) {
            unionSets(parent, rank, x, y);
            mstCost += cost;
            mstSize++;
            if (mstSize >= n * n / 2) break;
        }
    }

    printf("%d\n", mstCost);
    return 0;
}