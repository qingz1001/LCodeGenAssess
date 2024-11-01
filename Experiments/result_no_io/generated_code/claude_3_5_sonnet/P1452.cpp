#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50001

typedef struct {
    int x, y;
} Point;

Point points[MAX_N], hull[MAX_N];
int n, m;

long long cross(Point a, Point b, Point c) {
    return (long long)(b.x - a.x) * (c.y - a.y) - (long long)(b.y - a.y) * (c.x - a.x);
}

long long dist(Point a, Point b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    long long cross_product = cross(points[0], *p1, *p2);
    if (cross_product > 0) return -1;
    if (cross_product < 0) return 1;
    return (dist(points[0], *p1) <= dist(points[0], *p2)) ? -1 : 1;
}

void convex_hull() {
    int i, j;
    for (i = 1; i < n; i++) {
        if (points[i].y < points[0].y || (points[i].y == points[0].y && points[i].x < points[0].x)) {
            Point temp = points[0];
            points[0] = points[i];
            points[i] = temp;
        }
    }
    
    qsort(points + 1, n - 1, sizeof(Point), cmp);
    
    hull[0] = points[0];
    hull[1] = points[1];
    m = 2;
    
    for (i = 2; i < n; i++) {
        while (m > 1 && cross(hull[m-2], hull[m-1], points[i]) <= 0) {
            m--;
        }
        hull[m++] = points[i];
    }
}

long long rotating_calipers() {
    long long max_dist = 0;
    int i = 0, j = 0;
    for (int k = 0; k < m; k++) {
        if (hull[k].x < hull[i].x) i = k;
        if (hull[k].x > hull[j].x) j = k;
    }
    
    for (int k = 0; k < m; k++) {
        long long curr_dist = dist(hull[i], hull[j]);
        if (curr_dist > max_dist) max_dist = curr_dist;
        
        if (cross(hull[(i+1)%m], hull[i], hull[(j+1)%m]) <= cross(hull[(i+1)%m], hull[i], hull[j])) {
            j = (j + 1) % m;
        } else {
            i = (i + 1) % m;
        }
    }
    
    return max_dist;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    convex_hull();
    long long result = rotating_calipers();
    
    printf("%lld\n", result);
    
    return 0;
}