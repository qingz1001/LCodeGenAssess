#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    else
        return find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    Edge edges[M];
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), compare);

    int parent[N];
    int rank[N];

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int maxEdge = 0;
    int edgesUsed = 0;

    for (int i = 0; i < M && edgesUsed < N - 1; i++) {
        int u = edges[i].u - 1;
        int v = edges[i].v - 1;
        int weight = edges[i].w;

        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);
            maxEdge = weight;
            edgesUsed++;
        }
    }

    printf("%d\n", maxEdge);
    return 0;
}