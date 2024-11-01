#include <stdio.h>
#include <stdlib.h>

#define MAXN 20010
#define MAXM 100010

struct Edge {
    int u, v, w;
};

int n, m;
int parent[MAXN];
struct Edge edges[MAXM];

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeB->w - edgeA->w;
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
        parent[rootX] = rootY;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(struct Edge), compare);

    int minConflict = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            unionSets(u, v);
        } else {
            minConflict = w;
            break;
        }
    }

    printf("%d\n", minConflict);
    return 0;
}