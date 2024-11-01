#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

typedef struct {
    int u, v, w, c;
} Edge;

Edge edges[MAXM];
int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->c == edgeB->c) {
        return edgeA->w - edgeB->w;
    }
    return edgeA->c - edgeB->c;
}

int main() {
    int V, E, need;
    scanf("%d %d %d", &V, &E, &need);

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].w, &edges[i].c);
    }

    qsort(edges, E, sizeof(Edge), compare);

    init(V);

    int whiteCount = 0;
    int minWeight = 0;
    int i = 0;

    while (whiteCount < need && i < E) {
        if (edges[i].c == 0) {
            whiteCount++;
        }
        i++;
    }

    for (; i < E; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            minWeight += edges[i].w;
        }
    }

    printf("%d\n", minWeight);

    return 0;
}