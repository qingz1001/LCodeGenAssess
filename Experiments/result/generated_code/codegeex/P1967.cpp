#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 50001
#define MAXQ 30001

typedef struct Edge {
    int u, v, w;
} Edge;

Edge edges[MAXM];
int parent[MAXN], rank[MAXN];
int maxWeight[MAXN];

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeB->w - edgeA->w;
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
            maxWeight[rootX] = maxWeight[rootX] < maxWeight[rootY] ? maxWeight[rootY] : maxWeight[rootX];
        } else {
            parent[rootX] = rootY;
            if (rank[rootX] == rank[rootY]) {
                rank[rootY]++;
            }
            maxWeight[rootY] = maxWeight[rootX] < maxWeight[rootY] ? maxWeight[rootX] : maxWeight[rootY];
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
        maxWeight[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        unite(edges[i].u, edges[i].v);
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            printf("-1\n");
        } else {
            printf("%d\n", maxWeight[rootX]);
        }
    }

    return 0;
}