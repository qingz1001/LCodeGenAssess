#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double weight;
} Edge;

Point points[MAXN * 2];
Edge edges[MAXN * 2 * (MAXN * 2 - 1) / 2];
int parent[MAXN * 2];

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->weight > ((Edge *)b)->weight ? 1 : -1;
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%d %d %d %d", &AX, &AY, &BX, &BY);
    scanf("%d %d %d %d", &CX, &CY, &DX, &DY);

    double t;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &t);
        points[i].x = AX * t + BX * (1 - t);
        points[i].y = AY * t + BY * (1 - t);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lf", &t);
        points[n + i].x = CX * t + DX * (1 - t);
        points[n + i].y = CY * t + DY * (1 - t);
    }

    int edge_count = 0;
    for (int i = 0; i < n + m; i++) {
        for (int j = i + 1; j < n + m; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].weight = distance(points[i], points[j]);
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), cmp);

    for (int i = 0; i < n + m; i++) {
        parent[i] = i;
    }

    double mst_weight = 0.0;
    int edge_used = 0;
    for (int i = 0; i < edge_count && edge_used < n + m - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            union_set(u, v);
            mst_weight += edges[i].weight;
            edge_used++;
        }
    }

    printf("%.3f\n", mst_weight);

    return 0;
}