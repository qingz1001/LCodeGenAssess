#include <stdio.h>
#include <stdlib.h>

#define N 10001
#define M 40001

struct Edge {
    int u, v, a, b, id;
} edges[N];

int parent[N], rank[N];

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    if (edgeA->a * edgeB->b != edgeB->a * edgeA->b) {
        return edgeA->a * edgeB->b - edgeB->a * edgeA->b;
    } else {
        return edgeA->a - edgeB->a;
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
        edges[i].u++;
        edges[i].v++;
        edges[i].id = i;
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