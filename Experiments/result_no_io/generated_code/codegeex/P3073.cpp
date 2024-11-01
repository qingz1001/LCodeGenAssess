#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXM 250000

typedef struct {
    int x, y, d;
} Edge;

int n;
int height[MAXN][MAXN];
int visited[MAXN][MAXN];
Edge edges[MAXM];
int edgeCount;

void addEdge(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || x2 < 0 || x2 >= n || y2 < 0 || y2 >= n) return;
    int d = abs(height[x1][y1] - height[x2][y2]);
    edges[edgeCount++] = (Edge){x1, y1, d};
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->d - edgeB->d;
}

int find(int x, int *parent) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x], parent);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            addEdge(i, j, i - 1, j);
            addEdge(i, j, i, j - 1);
            addEdge(i, j, i + 1, j);
            addEdge(i, j, i, j + 1);
        }
    }

    qsort(edges, edgeCount, sizeof(Edge), compare);

    int target = (n * n + 1) / 2;
    int parent[n * n];
    for (int i = 0; i < n * n; i++) parent[i] = i;
    int components = n * n;

    for (int i = 0; i < edgeCount && components > target; i++) {
        int root1 = find(edges[i].x * n + edges[i].y, parent);
        int root2 = find(edges[i].d * n + edges[i].y, parent);
        if (root1 != root2) {
            parent[root1] = root2;
            components--;
        }
    }

    printf("%d\n", edges[edgeCount - components].d);
    return 0;
}