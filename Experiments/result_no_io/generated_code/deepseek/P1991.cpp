#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_P 500
#define MAX_S 100

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

Point points[MAX_P];
Edge edges[MAX_P * MAX_P];
int parent[MAX_P];

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
        parent[rootX] = rootY;
    }
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->dist > ((Edge *)b)->dist ? 1 : -1;
}

double kruskal(int P, int S) {
    int edge_count = 0;
    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            double dist = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) + 
                               (points[i].y - points[j].y) * (points[i].y - points[j].y));
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = dist;
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), compare);

    for (int i = 0; i < P; i++) {
        parent[i] = i;
    }

    int used_satellites = 0;
    double max_dist = 0.0;
    for (int i = 0; i < edge_count; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_set(edges[i].u, edges[i].v);
            max_dist = edges[i].dist;
            used_satellites++;
            if (used_satellites == P - S) {
                break;
            }
        }
    }

    return max_dist;
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    for (int i = 0; i < P; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    double result = kruskal(P, S);
    printf("%.2f\n", result);

    return 0;
}