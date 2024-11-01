#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

Point points[MAXN];
Edge edges[MAXN * MAXN];
int parent[MAXN];
int rank[MAXN];

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->dist > ((Edge *)b)->dist ? 1 : -1;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
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

double kruskal(int n, int k) {
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
                               (points[i].y - points[j].y) * (points[i].y - points[j].y));
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = dist;
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), cmp);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int components = n;
    for (int i = 0; i < edge_count; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            if (components == k) {
                return edges[i].dist;
            }
            union_set(edges[i].u, edges[i].v);
            components--;
        }
    }
    return 0.0;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    double result = kruskal(n, k);
    printf("%.2f\n", result);

    return 0;
}