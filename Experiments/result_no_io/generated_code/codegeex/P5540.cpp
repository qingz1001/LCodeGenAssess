#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 10001

struct Edge {
    int u, v, a, b, cost;
} edges[MAXM];

int parent[MAXN], rank[MAXN];

int compare(const void *a, const void *b) {
    return (*(struct Edge *)a).cost - (*(struct Edge *)b).cost;
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

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
        edges[i].u++;
        edges[i].v++;
        edges[i].cost = edges[i].a * edges[i].b;
    }

    qsort(edges, m, sizeof(struct Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    long long sumA = 0, sumB = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            sumA += edges[i].a;
            sumB += edges[i].b;
        }
    }

    printf("%lld %lld\n", sumA, sumB);

    return 0;
}