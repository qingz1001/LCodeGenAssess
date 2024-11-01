#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 50001
#define MAX_M 200001

typedef struct {
    int u, v, w;
} Edge;

int n, m;
Edge edges[MAX_M];
int parent[MAX_N];
int rank[MAX_N];

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

void init_set() {
    for (int i = 1; i <= n; i++) {
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
    if (px == py) return;
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

int kruskal(int start) {
    int max_edge = edges[start].w;
    int min_edge = edges[start].w;
    int count = 0;
    
    init_set();
    
    for (int i = start; i < m && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find_set(u) != find_set(v)) {
            union_sets(u, v);
            max_edge = edges[i].w;
            count++;
        }
    }
    
    return (count == n - 1) ? max_edge - min_edge : -1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    int min_diff = 1e9;
    for (int i = 0; i <= m - n + 1; i++) {
        int diff = kruskal(i);
        if (diff != -1 && diff < min_diff) {
            min_diff = diff;
        }
    }
    
    printf("%d\n", min_diff);
    
    return 0;
}