#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1005
#define INF 1e9

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double cost;
} Edge;

Point points[MAXN];
Edge edges[MAXN * MAXN];
int parent[MAXN];
double dist[MAXN];

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->cost > edgeB->cost;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

double calculateDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    double dirtRoadCost, romeRoadCost;
    int n, i, j, k, m, u, v;
    scanf("%lf %lf", &dirtRoadCost, &romeRoadCost);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    m = 0;
    while (1) {
        scanf("%d %d", &u, &v);
        if (u == 0 && v == 0) break;
        edges[m].u = u - 1;
        edges[m].v = v - 1;
        edges[m].cost = romeRoadCost;
        m++;
    }
    Point start, end;
    scanf("%lf %lf", &start.x, &start.y);
    scanf("%lf %lf", &end.x, &end.y);
    for (i = 0; i < n; i++) {
        edges[m].u = n;
        edges[m].v = i;
        edges[m].cost = calculateDistance(start, points[i]) * dirtRoadCost;
        m++;
        edges[m].u = i;
        edges[m].v = n;
        edges[m].cost = calculateDistance(start, points[i]) * dirtRoadCost;
        m++;
        edges[m].u = i;
        edges[m].v = n + 1;
        edges[m].cost = calculateDistance(end, points[i]) * dirtRoadCost;
        m++;
        edges[m].u = n + 1;
        edges[m].v = i;
        edges[m].cost = calculateDistance(end, points[i]) * dirtRoadCost;
        m++;
    }
    for (i = 0; i < n + 2; i++) {
        parent[i] = i;
        dist[i] = INF;
    }
    dist[n] = 0;
    qsort(edges, m, sizeof(Edge), compare);
    for (k = 0; k < m; k++) {
        u = edges[k].u;
        v = edges[k].v;
        if (find(u) != find(v)) {
            unionSets(u, v);
            dist[v] = edges[k].cost;
        }
    }
    printf("%.4lf\n", dist[n + 1]);
    return 0;
}