#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 100005
#define MAXQ 100005
#define MAXE 5005

typedef struct Edge {
    int u, v, w;
} Edge;

Edge edges[MAXM];
Edge removed[MAXE];
int parent[MAXN];
int rank[MAXN];
int minTime[MAXN][MAXN];
int n, m, q;

void init(int n) {
    for (int i = 0; i < n; i++) {
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

void kruskal() {
    init(n);
    memset(minTime, 0, sizeof(minTime));
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            unionSets(u, v);
            minTime[u][v] = minTime[v][u] = w;
        }
    }
}

void processQuery() {
    int currentSize = 0;
    for (int i = 0; i < q; i++) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        if (k == 1) {
            printf("%d\n", minTime[u][v]);
        } else {
            if (minTime[u][v] != 0) {
                removed[currentSize++] = (Edge){u, v, minTime[u][v]};
                minTime[u][v] = minTime[v][u] = 0;
            }
        }
    }
    for (int i = 0; i < currentSize; i++) {
        int u = removed[i].u;
        int v = removed[i].v;
        int w = removed[i].w;
        if (find(u) != find(v)) {
            unionSets(u, v);
            minTime[u][v] = minTime[v][u] = w;
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    kruskal();
    processQuery();
    return 0;
}