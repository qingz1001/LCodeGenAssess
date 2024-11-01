#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 5000
#define INF 1e18

typedef struct {
    int x, y;
} City;

typedef struct {
    int u, v;
    double dist;
} Edge;

City cities[MAX_N];
int parent[MAX_N];
Edge edges[MAX_N * MAX_N];
int edge_count = 0;

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int cmp(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->dist < eb->dist) return -1;
    if (ea->dist > eb->dist) return 1;
    return 0;
}

double distance(City a, City b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].x, &cities[i].y);
        parent[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = distance(cities[i], cities[j]);
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), cmp);

    double total_length = 0;
    int connected = 0;

    for (int i = 0; i < edge_count && connected < n - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            total_length += edges[i].dist;
            connected++;
        }
    }

    printf("%.2f\n", total_length);

    return 0;
}