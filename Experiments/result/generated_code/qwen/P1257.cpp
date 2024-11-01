#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int compare(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x != p2->x) return (p1->x > p2->x) - (p1->x < p2->x);
    else return (p1->y > p2->y) - (p1->y < p2->y);
}

double closest_pair(Point points[], int n) {
    qsort(points, n, sizeof(Point), compare);

    double min_dist = __DBL_MAX__;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n && (points[j].x - points[i].x) < min_dist; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < min_dist) min_dist = dist;
        }
    }

    return min_dist;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    double result = closest_pair(points, n);
    printf("%.4f\n", result);

    return 0;
}