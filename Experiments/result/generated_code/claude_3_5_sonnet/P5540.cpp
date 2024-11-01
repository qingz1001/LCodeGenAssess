#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 201
#define MAX_M 10001

typedef struct {
    int u, v, a, b;
} Edge;

Edge edges[MAX_M];
int parent[MAX_N];
int n, m;

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->a - ((Edge*)b)->a;
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

long long kruskal(double lambda) {
    for (int i = 0; i < n; i++) parent[i] = i;
    
    for (int i = 0; i < m; i++) {
        edges[i].a = edges[i].a - lambda * edges[i].b;
    }
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    long long a_sum = 0, b_sum = 0;
    for (int i = 0; i < m; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            a_sum += edges[i].a + lambda * edges[i].b;
            b_sum += edges[i].b;
        }
    }
    
    return a_sum;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }
    
    double left = 0, right = 256;
    while (right - left > 1e-8) {
        double mid = (left + right) / 2;
        if (kruskal(mid) >= 0) left = mid;
        else right = mid;
    }
    
    long long a_sum = 0, b_sum = 0;
    for (int i = 0; i < n; i++) parent[i] = i;
    
    for (int i = 0; i < m; i++) {
        edges[i].a = edges[i].a - left * edges[i].b;
    }
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    for (int i = 0; i < m; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            a_sum += edges[i].a + left * edges[i].b;
            b_sum += edges[i].b;
        }
    }
    
    printf("%lld %lld\n", a_sum, b_sum);
    
    return 0;
}