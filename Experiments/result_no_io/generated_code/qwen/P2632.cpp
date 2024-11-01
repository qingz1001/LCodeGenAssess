#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double w;
} Edge;

int n, m;
Point p1[MAXN], p2[MAXN];
Edge edges[MAXN * 2];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void add_edge(int u, int v, double w) {
    static int edge_count = 0;
    edges[edge_count].u = u;
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edge_count++;
}

int cmp(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->w < e2->w) return -1;
    if (e1->w > e2->w) return 1;
    return 0;
}

int find(int parent[], int i) {
    if (parent[i] == -1) return i;
    return find(parent, parent[i]);
}

void union_set(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int kruskal() {
    qsort(edges, n + m, sizeof(Edge), cmp);
    int parent[MAXN * 2];
    for (int i = 0; i < n + m; i++) parent[i] = -1;
    int edge_count = 0, i = 0;
    while (edge_count < n + m - 1 && i < n + m) {
        Edge next_edge = edges[i++];
        int x = find(parent, next_edge.u);
        int y = find(parent, next_edge.v);
        if (x != y) {
            union_set(parent, x, y);
            edge_count++;
        }
    }
    return edge_count == n + m - 1 ? 1 : 0;
}

int main() {
    scanf("%d %d", &n, &m);
    double AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%lf %lf %lf %lf", &AX, &AY, &BX, &BY);
    scanf("%lf %lf %lf %lf", &CX, &CY, &DX, &DY);

    for (int i = 0; i < n; i++) {
        double t;
        scanf("%lf", &t);
        p1[i].x = AX * t + BX * (1 - t);
        p1[i].y = AY * t + BY * (1 - t);
    }

    for (int i = 0; i < m; i++) {
        double t;
        scanf("%lf", &t);
        p2[i].x = CX * t + DX * (1 - t);
        p2[i].y = CY * t + DY * (1 - t);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            add_edge(i, j + n, dist(p1[i], p2[j]));
        }
    }

    double total_cost = 0.0;
    for (int i = 0; i < n; i++) {
        add_edge(i, i + n, 0.0);
        total_cost += dist(p1[i], p2[0]);
    }

    if (kruskal()) {
        printf("%.3f\n", total_cost);
    } else {
        printf("No solution\n");
    }

    return 0;
}