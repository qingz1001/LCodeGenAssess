#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 6
#define PI 3.14159265358979323846

typedef struct {
    int x, y;
} Point;

int N;
Point box[2];
Point points[MAXN];

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double max_radius(Point p, int index) {
    double min_dist = 1e9;
    for (int i = 0; i < N; i++) {
        if (i != index) {
            double d = distance(p, points[i]);
            if (d < min_dist) min_dist = d;
        }
    }
    for (int i = 0; i < 2; i++) {
        double d = fmin(fabs(p.x - box[i].x), fabs(p.y - box[i].y));
        if (d < min_dist) min_dist = d;
    }
    return min_dist;
}

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    double r1 = max_radius(*p1, -1);
    double r2 = max_radius(*p2, -1);
    if (r1 < r2) return 1;
    if (r1 > r2) return -1;
    return 0;
}

int main() {
    scanf("%d", &N);
    scanf("%d %d %d %d", &box[0].x, &box[0].y, &box[1].x, &box[1].y);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    double total_area = 0;
    for (int i = 0; i < N; i++) {
        double r = max_radius(points[i], i);
        total_area += PI * r * r;
    }

    double box_area = fabs((box[1].x - box[0].x) * (box[1].y - box[0].y));
    double remaining_area = box_area - total_area;

    printf("%.0f\n", round(remaining_area));

    return 0;
}