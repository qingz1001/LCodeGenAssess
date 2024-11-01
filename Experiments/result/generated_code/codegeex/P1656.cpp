#include <stdio.h>
#include <stdlib.h>

#define MAXN 151
#define MAXM 5001

int n, m;
int parent[MAXN];

typedef struct {
    int u, v;
} Edge;

Edge edges[MAXM];
Edge keyRoads[MAXM];

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->u != edgeB->u)
        return edgeA->u - edgeB->u;
    else
        return edgeA->v - edgeB->v;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        if (edges[i].u > edges[i].v) {
            int temp = edges[i].u;
            edges[i].u = edges[i].v;
            edges[i].v = temp;
        }
    }

    qsort(edges, m, sizeof(Edge), compare);

    int keyRoadCount = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            unionSets(u, v);
        } else {
            keyRoads[keyRoadCount++] = edges[i];
        }
    }

    qsort(keyRoads, keyRoadCount, sizeof(Edge), compare);

    for (int i = 0; i < keyRoadCount; i++) {
        printf("%d %d\n", keyRoads[i].u, keyRoads[i].v);
    }

    return 0;
}