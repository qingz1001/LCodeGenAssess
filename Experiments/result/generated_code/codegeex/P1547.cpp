#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    } else {
        return parent[i] = find(parent, parent[i]);
    }
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Edge edges[M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), compare);

    int parent[N + 1];
    int rank[N + 1];

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int maxWeight = 0;
    int edgesUsed = 0;

    for (int i = 0; i < M && edgesUsed < N - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);
            maxWeight = w;
            edgesUsed++;
        }
    }

    printf("%d\n", maxWeight);
    return 0;
}