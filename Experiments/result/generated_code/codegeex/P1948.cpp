#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_P 10001

struct Edge {
    int u, v, w;
};

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->w - edgeB->w;
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
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);

    struct Edge edges[MAX_P];
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, p, sizeof(struct Edge), compare);

    int parent[MAX_N];
    int rank[MAX_N];

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int minCost = 0;
    int freeCables = k;

    for (int i = 0; i < p; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(parent, u) != find(parent, v)) {
            if (freeCables > 0) {
                freeCables--;
            } else {
                minCost = w;
                break;
            }
            unionSets(parent, rank, u, v);
        }
    }

    if (find(parent, 1) != find(parent, n)) {
        printf("-1\n");
    } else {
        printf("%d\n", minCost);
    }

    return 0;
}