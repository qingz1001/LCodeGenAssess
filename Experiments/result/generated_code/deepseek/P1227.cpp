#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

int comparePoints(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) {
        return p1->x - p2->x;
    } else {
        return p1->y - p2->y;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Point *points = (Point *)malloc(N * sizeof(Point));
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), comparePoints);

    double centerX = (points[0].x + points[N-1].x) / 2.0;
    double centerY = (points[0].y + points[N-1].y) / 2.0;

    for (int i = 0; i < N / 2; i++) {
        double expectedX = 2 * centerX - points[i].x;
        double expectedY = 2 * centerY - points[i].y;
        if (expectedX != points[N-1-i].x || expectedY != points[N-1-i].y) {
            printf("This is a dangerous situation!\n");
            free(points);
            return 0;
        }
    }

    printf("V.I.P. should stay at (%.1f,%.1f).\n", centerX, centerY);
    free(points);
    return 0;
}