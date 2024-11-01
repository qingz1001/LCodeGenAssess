#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50005

typedef struct Point {
    int x, y;
} Point;

int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int cmp(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    int crs = cross(*pa, *pb, *(pa + 1));
    if (crs > 0) return -1;
    if (crs < 0) return 1;
    return dist(*pa, *(pa + 1)) < dist(*pb, *(pb + 1)) ? -1 : 1;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), cmp);

    int hullSize = 0;
    Point hull[MAXN * 2];
    hull[hullSize++] = points[0];
    hull[hullSize++] = points[1];
    for (int i = 2; i < n; i++) {
        while (hullSize > 1 && cross(hull[hullSize - 2], hull[hullSize - 1], points[i]) <= 0) {
            hullSize--;
        }
        hull[hullSize++] = points[i];
    }

    int t = hullSize;
    for (int i = n - 2; i >= 0; i--) {
        while (hullSize > t && cross(hull[hullSize - 2], hull[hullSize - 1], points[i]) <= 0) {
            hullSize--;
        }
        hull[hullSize++] = points[i];
    }

    double maxDist = 0;
    for (int i = 0; i < hullSize - 1; i++) {
        for (int j = i + 1; j < hullSize; j++) {
            maxDist = fmax(maxDist, dist(hull[i], hull[j]));
        }
    }

    printf("%.0lf\n", maxDist * maxDist);
    return 0;
}