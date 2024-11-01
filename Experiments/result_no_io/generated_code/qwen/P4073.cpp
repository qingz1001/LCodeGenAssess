#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005
#define MAXM 100005
#define INF 1e9

typedef struct {
    int u, v, h;
} Edge;

typedef struct {
    double x, y;
} Point;

int n, m, q;
Edge edges[MAXM];
Point points[MAXN];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    scanf("%d", &q);

    for (int qi = 0; qi < q; qi++) {
        double Ax, Ay, Bx, By;
        scanf("%lf %lf %lf %lf", &Ax, &Ay, &Bx, &By);
        Point A = {Ax, Ay};
        Point B = {Bx, By};

        double min_dist = INF;
        for (int i = 0; i < m; i++) {
            double d1 = dist(A, points[edges[i].u - 1]);
            double d2 = dist(B, points[edges[i].v - 1]);
            if (d1 + d2 < min_dist) {
                min_dist = d1 + d2;
            }
        }

        if (min_dist == INF) {
            printf("-1\n");
        } else {
            printf("%.0f\n", min_dist);
        }
    }

    return 0;
}