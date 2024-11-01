#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXP 40000

typedef struct {
    int a, b, l;
} Edge;

Edge edges[MAXP];
int parent[MAXN + 1];
int rank[MAXN + 1];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
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
    return ((Edge *)a)->l - ((Edge *)b)->l;
}

int kruskal(int n, int p, int t) {
    qsort(edges, p, sizeof(Edge), compare);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int max_edge = 0;
    int edge_count = 0;
    for (int i = 0; i < p && edge_count < t; i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        if (find(a) != find(b)) {
            union_set(a, b);
            max_edge = edges[i].l;
            edge_count++;
        }
    }

    return max_edge;
}

int main() {
    int n, p, t;
    scanf("%d %d %d", &n, &p, &t);

    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }

    int result = kruskal(n, p, t);
    printf("%d\n", result);

    return 0;
}