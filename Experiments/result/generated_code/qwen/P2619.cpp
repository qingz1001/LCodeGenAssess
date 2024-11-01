#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

typedef struct {
    int v, w, col;
} Edge;

int V, E, need;
Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int cmp(const void *a, const void *b) {
    Edge *e1 = (Edge *)a, *e2 = (Edge *)b;
    return e1->w - e2->w;
}

int kruskal() {
    for (int i = 0; i < V; i++) parent[i] = i;
    qsort(edges, E, sizeof(Edge), cmp);

    int cnt = 0, white_edges = 0, weight = 0;
    for (int i = 0; i < E && cnt < V - 1; i++) {
        int u = edges[i].v, v = edges[i].w, w = edges[i].col;
        if (find(u) != find(v)) {
            union_set(u, v);
            weight += w;
            cnt++;
            if (w == 0) white_edges++;
        }
    }

    if (white_edges == need) return weight;
    else return -1;
}

int main() {
    scanf("%d %d %d", &V, &E, &need);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d %d", &edges[i].v, &edges[i].w, &edges[i].col);
    }

    int result = kruskal();
    printf("%d\n", result);

    return 0;
}