#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int ccw(Point a, Point b, Point c) {
    int val = cross(a, b, c);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    int val = ccw(p1, p2, &p1[1]);
    if (val != 0) return val;
    return dist(p1[0], p1[1]) - dist(p2[0], p2[1]);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), cmp);

    int hull[n];
    int top = 0;
    hull[top++] = 0;
    hull[top++] = 1;
    for (int i = 2; i < n; i++) {
        while (top >= 2 && ccw(points[hull[top - 2]], points[hull[top - 1]], points[i]) <= 0) {
            top--;
        }
        hull[top++] = i;
    }
    int m = top;

    hull[top++] = n - 2;
    hull[top++] = n - 1;
    for (int i = n - 3; i >= 0; i--) {
        while (top >= m + 2 && ccw(points[hull[top - 2]], points[hull[top - 1]], points[i]) <= 0) {
            top--;
        }
        hull[top++] = i;
    }

    double maxd = 0;
    for (int i = 0; i < top - 1; i++) {
        for (int j = i + 1; j < top; j++) {
            maxd = fmax(maxd, dist(points[hull[i]], points[hull[j]]));
        }
    }

    printf("%lld\n", (long long)(maxd * maxd));
    return 0;
}