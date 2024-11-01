#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->y - p2->y) || (p1->x - p2->x);
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int N;
    scanf("%d", &N);
    int x, y, xp, yp;
    scanf("%d %d %d %d", &x, &y, &xp, &yp);
    Point points[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    double max_area = 0;
    for (int i = 0; i < N; i++) {
        double min_distance = INFINITY;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                min_distance = fmin(min_distance, distance(points[i], points[j]));
            }
        }
        double radius = min_distance / 2;
        double area = PI * radius * radius;
        max_area = fmax(max_area, area);
    }

    int box_width = abs(xp - x);
    int box_height = abs(yp - y);
    double total_area = box_width * box_height;
    double remaining_area = total_area - max_area;

    printf("%.0f\n", remaining_area);

    return 0;
}