#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100001
#define MAXM 300001

typedef struct Edge {
    int u, v, w;
} Edge;

int parent[MAXN], size[MAXN];
Edge edges[MAXM];
int n, m, q;

void init_union_find() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
}

void kruskal() {
    init_union_find();
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            union_sets(u, v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].u--; edges[i].v--; // Convert to 0-based index
    }
    kruskal();
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--; // Convert to 0-based index
        if (find(a) != find(b)) {
            printf("impossible\n");
        } else {
            int min_w = INT_MAX;
            for (int j = 0; j < m; j++) {
                if (find(edges[j].u) == find(edges[j].v)) {
                    min_w = edges[j].w;
                    break;
                }
            }
            printf("%d\n", min_w);
        }
    }
    return 0;
}