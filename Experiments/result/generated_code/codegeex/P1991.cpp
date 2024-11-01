#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int compare(const void *a, const void *b) {
    double distA = *(double *)a;
    double distB = *(double *)b;
    if (distA < distB) return -1;
    if (distA > distB) return 1;
    return 0;
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    Point *points = (Point *)malloc(P * sizeof(Point));
    double *distances = (double *)malloc(P * (P - 1) / 2 * sizeof(double));
    int index = 0;

    for (int i = 0; i < P; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            distances[index++] = distance(points[i], points[j]);
        }
    }

    qsort(distances, index, sizeof(double), compare);

    double D = distances[(P - S - 1) * (P - S) / 2];

    printf("%.2f\n", D);

    free(points);
    free(distances);

    return 0;
}