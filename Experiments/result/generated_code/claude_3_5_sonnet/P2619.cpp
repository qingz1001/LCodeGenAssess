#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 50005
#define MAXE 100005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int u, v, w, color;
} Edge;

Edge edges[MAXE];
int parent[MAXV];
int rank[MAXV];
int V, E, need;

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

void init_set() {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

int kruskal(int k) {
    int total_weight = 0;
    int white_count = 0;
    int edge_count = 0;

    for (int i = 0; i < E && edge_count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find_set(u) != find_set(v)) {
            if (edges[i].color == 0 && white_count < k) {
                union_set(u, v);
                total_weight += edges[i].w;
                white_count++;
                edge_count++;
            } else if (edges[i].color == 1 && edge_count - white_count < V - 1 - k) {
                union_set(u, v);
                total_weight += edges[i].w;
                edge_count++;
            }
        }
    }

    return (white_count == k && edge_count == V - 1) ? total_weight : INF;
}

int main() {
    scanf("%d %d %d", &V, &E, &need);

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].w, &edges[i].color);
    }

    qsort(edges, E, sizeof(Edge), cmp);

    init_set();
    int result = kruskal(need);

    if (result == INF)
        printf("No solution\n");
    else
        printf("%d\n", result);

    return 0;
}