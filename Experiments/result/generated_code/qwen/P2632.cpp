#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200000

typedef struct {
    int u, v;
    double w;
} Edge;

int parent[MAXN];
double rank[MAXN];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        if (rank[px] > rank[py]) {
            parent[py] = px;
        } else if (rank[px] < rank[py]) {
            parent[px] = py;
        } else {
            parent[px] = py;
            rank[py]++;
        }
    }
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &AX, &AY, &BX, &BY, &CX, &CY, &DX, &DY);

    double points1[n], points2[m];
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &points1[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%lf", &points2[i]);
    }

    Edge edges[MAXN * 3];

    // Edges between points on the same line
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double x1 = AX * points1[i] + BX * (1 - points1[i]);
            double y1 = AY * points1[i] + BY * (1 - points1[i]);
            double x2 = AX * points1[j] + BX * (1 - points1[j]);
            double y2 = AY * points1[j] + BY * (1 - points1[j]);
            edges[i * n + j].u = i;
            edges[i * n + j].v = j;
            edges[i * n + j].w = dist(x1, y1, x2, y2);
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            double x1 = CX * points2[i] + DX * (1 - points2[i]);
            double y1 = CY * points2[i] + DY * (1 - points2[i]);
            double x2 = CX * points2[j] + DX * (1 - points2[j]);
            double y2 = CY * points2[j] + DY * (1 - points2[j]);
            edges[(i + n) * (i + n) + j].u = i + n;
            edges[(i + n) * (i + n) + j].v = j + n;
            edges[(i + n) * (i + n) + j].w = dist(x1, y1, x2, y2);
        }
    }

    // Edges between points from different lines
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double x1 = AX * points1[i] + BX * (1 - points1[i]);
            double y1 = AY * points1[i] + BY * (1 - points1[i]);
            double x2 = CX * points2[j] + DX * (1 - points2[j]);
            double y2 = CY * points2[j] + DY * (1 - points2[j]);
            edges[i * n + (j + n)].u = i;
            edges[i * n + (j + n)].v = j + n;
            edges[i * n + (j + n)].w = dist(x1, y1, x2, y2);
        }
    }

    init(n + m);

    qsort(edges, n * m * 3, sizeof(Edge), [](const void* a, const void* b) {
        return ((Edge*)a)->w < ((Edge*)b)->w ? -1 : 1;
    });

    double mst_weight = 0;
    int edge_count = 0;

    for (int i = 0; i < n * m * 3 && edge_count < n + m - 1; ++i) {
        Edge e = edges[i];
        int pu = find(e.u);
        int pv = find(e.v);
        if (pu != pv) {
            unionSet(pu, pv);
            mst_weight += e.w;
            edge_count++;
        }
    }

    printf("%.3f\n", mst_weight);

    return 0;
}