#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->x - p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    int max_time = 0;
    for (int i = 1; i < n; i++) {
        int time = (abs(points[i].x - points[i-1].x) + abs(points[i].y - points[i-1].y)) / 2;
        if (time > max_time) {
            max_time = time;
        }
    }

    printf("%d\n", max_time);
    return 0;
}