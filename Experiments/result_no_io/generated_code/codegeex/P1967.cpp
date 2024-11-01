#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 50001
#define MAXQ 30001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];
int parent[MAXN];
int rank[MAXN];

void initialize(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
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

    initialize(n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // Kruskal's algorithm to construct the maximum spanning tree
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            unionSets(u, v);
        }
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
            int maxWeight = -1;
            for (int j = 0; j < m; j++) {
                if ((edges[j].u == x && edges[j].v == y) || (edges[j].u == y && edges[j].v == x)) {
                    maxWeight = edges[j].w;
                    break;
                }
            }
            printf("%d\n", maxWeight);
        }
    }

    return 0;
}