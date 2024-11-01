#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 32
#define MAXM 1000

typedef struct {
    int from, to, cost;
} Edge;

Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
    }

    qsort(edges, M, sizeof(Edge), compare);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int minCost = 0;
    int minEdges = 0;

    for (int i = 0; i < M; i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        int cost = edges[i].cost;

        if (find(from) != find(to)) {
            union_set(from, to);
        } else {
            minCost += cost;
            minEdges++;
        }
    }

    printf("%d %d\n", minCost, minEdges);

    return 0;
}