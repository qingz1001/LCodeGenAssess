#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50005

typedef struct {
    int x, y;
} Point;

Point points[MAXN];
Point hull[MAXN];

int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int orientation(Point p, Point q, Point r) {
    int val = cross(p, q, r);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

void convexHull(int n) {
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    int p = l, q;
    do {
        hull[n++] = points[p];
        q = (p + 1) % n;
        for (int r = 0; r < n; r++) {
            if (orientation(points[p], points[q], points[r]) == 2)
                q = r;
        }
        p = q;
    } while (p != l);
}

int distanceSquared(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &points[i].x, &points[i].y);

    convexHull(n);

    int maxDist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            maxDist = fmax(maxDist, distanceSquared(hull[i], hull[j]));
        }
    }

    printf("%d\n", maxDist);
    return 0;
}