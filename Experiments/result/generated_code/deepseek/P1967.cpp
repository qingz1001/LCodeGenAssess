#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10000
#define MAXM 50000

typedef struct {
    int x, y, z;
} Edge;

int parent[MAXN + 1];
int rank[MAXN + 1];
Edge edges[MAXM];

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
    return ((Edge *)b)->z - ((Edge *)a)->z;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < m; i++) {
        union_sets(edges[i].x, edges[i].y);
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (find(x) == find(y)) {
            int max_weight = INT_MAX;
            for (int j = 0; j < m; j++) {
                if (find(edges[j].x) == find(x) && find(edges[j].y) == find(y)) {
                    if (edges[j].z < max_weight) {
                        max_weight = edges[j].z;
                    }
                }
            }
            printf("%d\n", max_weight);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}