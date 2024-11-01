#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 20005

typedef struct {
    int a, b, Ti, ti;
} Edge;

int n, k, m;
Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
    }

    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    qsort(edges, m, sizeof(Edge), [](const void *a, const void *b) {
        Edge *e1 = (Edge *)a;
        Edge *e2 = (Edge *)b;
        return e1->Ti - e2->Ti;
    });

    int result = 0;
    int used = 0;

    for (int i = 0; i < m && used < k + n - 1; ++i) {
        int u = edges[i].a;
        int v = edges[i].b;
        int Tu = edges[i].Ti;
        int Tu_kiana = edges[i].ti;

        if (find(u) != find(v)) {
            if (used < k) {
                result = Tu;
                used++;
            } else {
                result = Tu_kiana;
            }
            union_sets(u, v);
        }
    }

    printf("%d\n", result);

    return 0;
}