#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50001
#define MAX_M 200001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX_M];
int parent[MAX_N];
int n, m;

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int kruskal(int start) {
    int count = 0, max_weight = 0, min_weight = 1e9;
    
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    
    for (int i = start; i < m && count < n - 1; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            unite(u, v);
            count++;
            max_weight = w;
            min_weight = (w < min_weight) ? w : min_weight;
        }
    }
    
    return (count == n - 1) ? max_weight - min_weight : -1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    int result = 1e9;
    for (int i = 0; i <= m - n + 1; i++) {
        int diff = kruskal(i);
        if (diff != -1 && diff < result)
            result = diff;
    }
    
    printf("%d\n", result);
    
    return 0;
}