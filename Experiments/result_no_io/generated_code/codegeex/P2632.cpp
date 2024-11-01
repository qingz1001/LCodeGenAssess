#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int compare(const void *a, const void *b) {
    return (*(double*)a > *(double*)b) ? 1 : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int AX, AY, BX, BY, CX, CY, DX, DY;
    scanf("%d %d %d %d %d %d %d %d", &AX, &AY, &BX, &BY, &CX, &CY, &DX, &DY);

    double *t1 = (double*)malloc(n * sizeof(double));
    double *t2 = (double*)malloc(m * sizeof(double));

    for (int i = 0; i < n; i++) {
        scanf("%lf", &t1[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lf", &t2[i]);
    }

    qsort(t1, n, sizeof(double), compare);
    qsort(t2, m, sizeof(double), compare);

    Point *points1 = (Point*)malloc(n * sizeof(Point));
    Point *points2 = (Point*)malloc(m * sizeof(Point));

    for (int i = 0; i < n; i++) {
        points1[i].x = AX * t1[i] + BX * (1 - t1[i]);
        points1[i].y = AY * t1[i] + BY * (1 - t1[i]);
    }

    for (int i = 0; i < m; i++) {
        points2[i].x = CX * t2[i] + DX * (1 - t2[i]);
        points2[i].y = CY * t2[i] + DY * (1 - t2[i]);
    }

    double minTreeLength = 0.0;

    for (int i = 0; i < n; i++) {
        double minDist = INFINITY;
        for (int j = 0; j < m; j++) {
            double dist = distance(points1[i], points2[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
        minTreeLength += minDist;
    }

    printf("%.3lf\n", minTreeLength);

    free(t1);
    free(t2);
    free(points1);
    free(points2);

    return 0;
}