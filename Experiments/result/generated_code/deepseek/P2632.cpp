#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double w;
} Edge;

Point points[MAXN * 2];
Edge edges[MAXN * MAXN];
int parent[MAXN * 2];

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w > ((Edge *)b)->w ? 1 : -1;
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

double kruskal(int n, int m, int edge_count) {
    qsort(edges, edge_count, sizeof(Edge), cmp);
    for (int i = 0; i < n + m; i++) parent[i] = i;

    double mst_weight = 0.0;
    int edge_used = 0;

    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        double w = edges[i].w;

        if (find(u) != find(v)) {
            union_set(u, v);
            mst_weight += w;
            edge_used++;
            if (edge_used == n + m - 1) break;
        }
    }

    return mst_weight;
}

int main() {
    int n, m;
    double AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%d %d", &n, &m);
    scanf("%lf %lf %lf %lf", &AX, &AY, &BX, &BY);
    scanf("%lf %lf %lf %lf", &CX, &CY, &DX, &DY);

    for (int i = 0; i < n; i++) {
        double t;
        scanf("%lf", &t);
        points[i].x = AX * t + BX * (1 - t);
        points[i].y = AY * t + BY * (1 - t);
    }

    for (int i = 0; i < m; i++) {
        double t;
        scanf("%lf", &t);
        points[n + i].x = CX * t + DX * (1 - t);
        points[n + i].y = CY * t + DY * (1 - t);
    }

    int edge_count = 0;
    for (int i = 0; i < n + m; i++) {
        for (int j = i + 1; j < n + m; j++) {
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].w = sqrt(dx * dx + dy * dy);
            edge_count++;
        }
    }

    double result = kruskal(n, m, edge_count);
    printf("%.3f\n", result);

    return 0;
}