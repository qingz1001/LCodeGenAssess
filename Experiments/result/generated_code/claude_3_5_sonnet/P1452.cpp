#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50001

typedef struct {
    int x, y;
} Point;

Point points[MAXN], stack[MAXN];
int n, top;

long long cross(Point a, Point b, Point c) {
    return (long long)(b.x - a.x) * (c.y - a.y) - (long long)(b.y - a.y) * (c.x - a.x);
}

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    long long c = cross(points[0], *p1, *p2);
    if (c > 0) return -1;
    if (c < 0) return 1;
    long long d1 = (long long)(p1->x - points[0].x) * (p1->x - points[0].x) + (long long)(p1->y - points[0].y) * (p1->y - points[0].y);
    long long d2 = (long long)(p2->x - points[0].x) * (p2->x - points[0].x) + (long long)(p2->y - points[0].y) * (p2->y - points[0].y);
    return (d1 < d2) ? -1 : (d1 > d2);
}

void graham_scan() {
    int i, j;
    for (i = 1; i < n; i++)
        if (points[i].y < points[0].y || (points[i].y == points[0].y && points[i].x < points[0].x))
            { Point tmp = points[0]; points[0] = points[i]; points[i] = tmp; }
    
    qsort(points + 1, n - 1, sizeof(Point), cmp);
    
    stack[0] = points[0];
    stack[1] = points[1];
    top = 1;
    
    for (i = 2; i < n; i++) {
        while (top && cross(stack[top-1], stack[top], points[i]) <= 0) top--;
        stack[++top] = points[i];
    }
}

long long dist(Point a, Point b) {
    return (long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y);
}

long long rotating_calipers() {
    long long max_dist = 0;
    int i = 0, j = 0;
    for (int k = 0; k < top; k++) {
        if (stack[i].x < stack[k].x) i = k;
        if (stack[j].x > stack[k].x) j = k;
    }
    
    for (int k = 0; k < top; k++) {
        max_dist = (max_dist > dist(stack[i], stack[j])) ? max_dist : dist(stack[i], stack[j]);
        if (cross(stack[i], stack[(i+1)%top], stack[j]) < cross(stack[i], stack[(i+1)%top], stack[(j+1)%top]))
            j = (j + 1) % top;
        else
            i = (i + 1) % top;
    }
    
    return max_dist;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);
    
    graham_scan();
    printf("%lld\n", rotating_calipers());
    
    return 0;
}