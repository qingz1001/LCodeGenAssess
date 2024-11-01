#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

int V, E, need;
int fa[MAXN];

struct Edge {
    int u, v, w, col;
} edges[MAXM];

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    if (edgeA->w != edgeB->w) {
        return edgeA->w - edgeB->w;
    } else {
        return edgeA->col - edgeB->col;
    }
}

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        fa[rootX] = rootY;
    }
}

int main() {
    scanf("%d%d%d", &V, &E, &need);
    for (int i = 0; i < E; i++) {
        scanf("%d%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w, &edges[i].col);
        edges[i].u--;
        edges[i].v--;
    }

    qsort(edges, E, sizeof(struct Edge), compare);

    int totalWeight = 0;
    int whiteCount = 0;
    for (int i = 0; i < V; i++) {
        fa[i] = i;
    }

    for (int i = 0; i < E; i++) {
        if (whiteCount < need && edges[i].col == 0) {
            if (find(edges[i].u) != find(edges[i].v)) {
                unionSets(edges[i].u, edges[i].v);
                totalWeight += edges[i].w;
                whiteCount++;
            }
        } else if (edges[i].col == 1) {
            if (find(edges[i].u) != find(edges[i].v)) {
                unionSets(edges[i].u, edges[i].v);
                totalWeight += edges[i].w;
            }
        }
    }

    printf("%d\n", totalWeight);
    return 0;
}