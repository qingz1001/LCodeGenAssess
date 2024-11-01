#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 20000

typedef struct {
    double x, y;
} Point;

int comparePoints(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return (p1->x > p2->x) - (p1->x < p2->x);
    return (p1->y > p2->y) - (p1->y < p2->y);
}

int main() {
    int N;
    Point points[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), comparePoints);

    double centerX = (points[0].x + points[N-1].x) / 2.0;
    double centerY = (points[0].y + points[N-1].y) / 2.0;

    for (int i = 0; i < N; i++) {
        double mirrorX = 2 * centerX - points[i].x;
        double mirrorY = 2 * centerY - points[i].y;
        int found = 0;
        for (int j = 0; j < N; j++) {
            if (fabs(points[j].x - mirrorX) < 1e-6 && fabs(points[j].y - mirrorY) < 1e-6) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("This is a dangerous situation!\n");
            return 0;
        }
    }

    printf("V.I.P. should stay at (%.1lf,%.1lf).\n", centerX, centerY);
    return 0;
}