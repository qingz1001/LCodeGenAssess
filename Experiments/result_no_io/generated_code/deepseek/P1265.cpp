#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 5000

typedef struct {
    int x, y;
} City;

typedef struct {
    int u, v;
    double dist;
} Edge;

City cities[MAXN];
Edge edges[MAXN * MAXN];
int parent[MAXN];
int rank[MAXN];

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

int compare_edges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->dist < edgeB->dist) return -1;
    if (edgeA->dist > edgeB->dist) return 1;
    return 0;
}

double kruskal(int n, int edge_count) {
    qsort(edges, edge_count, sizeof(Edge), compare_edges);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    double total_length = 0.0;
    int edges_added = 0;

    for (int i = 0; i < edge_count && edges_added < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            union_set(u, v);
            total_length += edges[i].dist;
            edges_added++;
        }
    }

    return total_length;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].x, &cities[i].y);
    }

    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = sqrt((cities[i].x - cities[j].x) * (cities[i].x - cities[j].x) +
                               (cities[i].y - cities[j].y) * (cities[i].y - cities[j].y));
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = dist;
            edge_count++;
        }
    }

    double total_length = kruskal(n, edge_count);
    printf("%.2f\n", total_length);

    return 0;
}