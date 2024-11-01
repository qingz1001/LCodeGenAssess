#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int compare(const void *a, const void *b) {
    double diff = ((Point *)a)->x - ((Point *)b)->x;
    return (diff < 0) ? -1 : ((diff > 0) ? 1 : 0);
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closestPair(Point *points, int n) {
    if (n <= 1) return 0.0;
    
    qsort(points, n, sizeof(Point), compare);
    
    double minDist = distance(points[0], points[1]);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n && (points[j].y - points[i].y) < minDist; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < minDist) minDist = dist;
        }
    }
    return minDist;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Point *points = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    
    double result = closestPair(points, n);
    printf("%.4lf\n", result);
    
    free(points);
    return 0;
}