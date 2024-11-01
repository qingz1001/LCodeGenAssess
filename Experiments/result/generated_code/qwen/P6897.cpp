#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double min_time(int n, Point *a, int m, Point *b) {
    if (dist(a[0], b[0]) > 1) return -1;
    double lo = 0, hi = 1e9;
    while (hi - lo > EPS) {
        double mid = (lo + hi) / 2;
        Point ac = {a[0].x + mid, a[0].y};
        Point bc = {b[0].x + mid, b[0].y};
        if (dist(ac, bc) <= 1) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    int n, m;
    scanf("%d", &n);
    Point *a = malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &a[i].x, &a[i].y);
    }
    scanf("%d", &m);
    Point *b = malloc(m * sizeof(Point));
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &b[i].x, &b[i].y);
    }

    double t = min_time(n, a, m, b);
    if (t == -1) {
        printf("impossible\n");
    } else {
        printf("%.5f\n", t);
    }

    free(a);
    free(b);
    return 0;
}