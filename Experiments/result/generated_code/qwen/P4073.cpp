#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int u, v;
    int h;
} Edge;

typedef struct {
    double x, y;
} Point;

int n, m, q;
Point points[MAXN];
Edge edges[MAXN];
double queries[4 * MAXN];

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%lf %lf %lf %lf", &queries[4 * i], &queries[4 * i + 1], &queries[4 * i + 2], &queries[4 * i + 3]);
    }

    // Process each query
    for (int i = 0; i < q; ++i) {
        double Ax = queries[4 * i], Ay = queries[4 * i + 1];
        double Bx = queries[4 * i + 2], By = queries[4 * i + 3];

        double min_cost = INF;
        for (int j = 0; j < m; ++j) {
            double cost = dist(points[edges[j].u - 1], points[edges[j].v - 1]);
            if (cost < min_cost) {
                min_cost = cost;
            }
        }

        if (min_cost == INF) {
            printf("-1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}