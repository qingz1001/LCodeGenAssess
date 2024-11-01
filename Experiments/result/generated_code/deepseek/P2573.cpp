#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int n, m;
int height[MAXN];
Edge edges[MAXM];
int parent[MAXN];
int rank[MAXN];

int cmp(const void *a, const void *b) {
    return ((Edge *)b)->w - ((Edge *)a)->w;
}

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

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &height[i]);
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        if (height[u] >= height[v]) {
            edges[i].u = u;
            edges[i].v = v;
            edges[i].w = k;
        } else {
            edges[i].u = v;
            edges[i].v = u;
            edges[i].w = k;
        }
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int max_nodes = 1;
    long long min_distance = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            union_set(u, v);
            max_nodes++;
            min_distance += w;
        }

        if (max_nodes == n) break;
    }

    printf("%d %lld\n", max_nodes, min_distance);

    return 0;
}