#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 50001
#define MAX_E 100001
#define INF 0x3f3f3f3f

typedef struct Edge {
    int u, v, w, color;
} Edge;

Edge edges[MAX_E];
int parent[MAX_V];
int rank[MAX_V];
int V, E, need;

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

void init_sets() {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_set(int x) {
    if (x != parent[x])
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
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

long long kruskal(int white_count) {
    long long total_weight = 0;
    int edges_count = 0;
    init_sets();

    for (int i = 0; i < E && edges_count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find_set(u) != find_set(v)) {
            if ((edges[i].color == 0 && white_count > 0) || 
                (edges[i].color == 1 && white_count == 0)) {
                union_sets(u, v);
                total_weight += edges[i].w;
                edges_count++;
                if (edges[i].color == 0) white_count--;
            }
        }
    }

    return (edges_count == V - 1 && white_count == 0) ? total_weight : INF;
}

int main() {
    scanf("%d %d %d", &V, &E, &need);

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].w, &edges[i].color);
    }

    qsort(edges, E, sizeof(Edge), cmp);

    long long result = kruskal(need);
    
    if (result == INF) {
        printf("No solution\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}