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
int parent[MAXN], rank[MAXN];

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

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->dist > ((Edge *)b)->dist ? 1 : -1;
}

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        parent[i] = i;
        rank[i] = 0;
    }

    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = calculate_distance(points[i], points[j]);
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), cmp);

    int components = n;
    double result = 0.0;
    for (int i = 0; i < edge_count; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_set(edges[i].u, edges[i].v);
            components--;
            if (components == k) {
                result = edges[i].dist;
                break;
            }
        }
    }

    printf("%.2f\n", result);
    return 0;
}