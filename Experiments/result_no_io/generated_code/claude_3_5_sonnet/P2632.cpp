#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000
#define MAX_M 100000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double w;
} Edge;

Point points[MAX_N + MAX_M];
Edge edges[(MAX_N + MAX_M) * (MAX_N + MAX_M - 1) / 2];
int parent[MAX_N + MAX_M];

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w > ((Edge*)b)->w ? 1 : -1;
}

int find(int x) {
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double ax, ay, bx, by, cx, cy, dx, dy;
    scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
    scanf("%lf %lf %lf %lf", &cx, &cy, &dx, &dy);

    for (int i = 0; i < n; i++) {
        double t;
        scanf("%lf", &t);
        points[i].x = ax * t + bx * (1 - t);
        points[i].y = ay * t + by * (1 - t);
    }

    for (int i = 0; i < m; i++) {
        double t;
        scanf("%lf", &t);
        points[n + i].x = cx * t + dx * (1 - t);
        points[n + i].y = cy * t + dy * (1 - t);
    }

    int edge_count = 0;
    for (int i = 0; i < n + m; i++) {
        for (int j = i + 1; j < n + m; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].w = dist(points[i], points[j]);
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), cmp);

    for (int i = 0; i < n + m; i++) {
        parent[i] = i;
    }

    double mst_weight = 0;
    int selected_edges = 0;

    for (int i = 0; i < edge_count && selected_edges < n + m - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            mst_weight += edges[i].w;
            selected_edges++;
        }
    }

    printf("%.3f\n", mst_weight);

    return 0;
}