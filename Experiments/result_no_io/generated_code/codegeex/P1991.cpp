#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

int compare(const void *a, const void *b) {
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    return (pointA->x - pointB->x);
}

double calculateDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    Point *points = (Point *)malloc(P * sizeof(Point));
    for (int i = 0; i < P; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, P, sizeof(Point), compare);

    double minDistance = calculateDistance(points[0], points[1]);
    for (int i = 0; i < P - 1; i++) {
        for (int j = i + 1; j < P; j++) {
            double distance = calculateDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }

    printf("%.2lf\n", minDistance / 2.0);
    free(points);

    return 0;
}