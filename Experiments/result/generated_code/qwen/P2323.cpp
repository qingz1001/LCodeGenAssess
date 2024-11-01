#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 20005

typedef struct {
    int u, v, c1, c2;
} Edge;

int n, k, m;
Edge edges[MAXM];
int parent[MAXN], rank[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;
    if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[px] = py;
        if (rank[px] == rank[py])
            rank[py]++;
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < m - 1; ++i) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].c1, &edges[i].c2);
    }

    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by the cost of the first type of road in descending order
    qsort(edges, m - 1, sizeof(Edge), [](const void *a, const void *b) {
        Edge *ea = (Edge *)a;
        Edge *eb = (Edge *)b;
        return eb->c1 - ea->c1;
    });

    int count = 0, max_cost = 0;
    for (int i = 0; i < m - 1; ++i) {
        int pu = find(edges[i].u);
        int pv = find(edges[i].v);
        if (pu != pv) {
            union_set(pu, pv);
            count++;
            max_cost = edges[i].c1;
            if (count >= n - 1) break;
        }
    }

    printf("%d\n", max_cost);

    // Find the minimum spanning tree with at least k edges of the first type
    for (int i = 0; i < m - 1; ++i) {
        int pu = find(edges[i].u);
        int pv = find(edges[i].v);
        if (pu != pv) {
            union_set(pu, pv);
            count++;
            if (count >= n - 1) break;
        }
    }

    for (int i = 0; i < m - 1; ++i) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_set(edges[i].u, edges[i].v);
            printf("%d %d\n", i + 1, 1);
        }
    }

    return 0;
}