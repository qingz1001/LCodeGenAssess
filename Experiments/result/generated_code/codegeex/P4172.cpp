#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 100001
#define MAXQ 100001
#define MAXE 5001

typedef struct Edge {
    int u, v, w;
} Edge;

Edge edges[MAXM];
Edge removed[MAXE];
int parent[MAXN];
int rank[MAXN];
int minTime[MAXN][MAXN];
int removedCount;

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    removedCount = 0;
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

void addEdge(int u, int v, int w) {
    edges[removedCount].u = u;
    edges[removedCount].v = v;
    edges[removedCount].w = w;
    removedCount++;
}

void removeEdge(int u, int v, int w) {
    removed[removedCount].u = u;
    removed[removedCount].v = v;
    removed[removedCount].w = w;
    removedCount++;
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < m; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        addEdge(u, v, t);
    }

    for (int i = 0; i < q; i++) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);

        if (k == 1) {
            init(n);
            for (int j = 0; j < removedCount; j++) {
                if (removed[j].u != u && removed[j].v != v) {
                    unionSets(removed[j].u, removed[j].v);
                }
            }
            int minW = 0x7fffffff;
            for (int j = 0; j < removedCount; j++) {
                if (find(removed[j].u) == find(removed[j].v)) {
                    minW = removed[j].w;
                }
            }
            for (int j = 0; j < m; j++) {
                if (edges[j].u != u && edges[j].v != v) {
                    unionSets(edges[j].u, edges[j].v);
                }
            }
            int maxW = 0;
            for (int j = 0; j < m; j++) {
                if (find(edges[j].u) == find(edges[j].v)) {
                    maxW = max(maxW, edges[j].w);
                }
            }
            printf("%d\n", max(maxW, minW));
        } else if (k == 2) {
            removeEdge(u, v, 0);
        }
    }

    return 0;
}