#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

int cross(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int dist2(Point A, Point B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    Point hull[n];
    int k = 0;

    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) <= 0) k--;
        hull[k++] = points[i];
    }

    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(hull[k-2], hull[k-1], points[i]) <= 0) k--;
        hull[k++] = points[i];
    }

    k--;

    if (k == 2) {
        printf("%d\n", dist2(hull[0], hull[1]));
        return 0;
    }

    int maxDist2 = 0;
    int j = 1;
    for (int i = 0; i < k; i++) {
        while (cross(hull[i], hull[(i+1)%k], hull[(j+1)%k]) > cross(hull[i], hull[(i+1)%k], hull[j])) {
            j = (j + 1) % k;
        }
        maxDist2 = fmax(maxDist2, fmax(dist2(hull[i], hull[j]), dist2(hull[(i+1)%k], hull[j])));
    }

    printf("%d\n", maxDist2);
    return 0;
}