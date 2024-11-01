#include <stdio.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    int n;
    scanf("%d", &n);
    Point disks[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf", &disks[i].x, &disks[i].y, &disks[i].x);
    }

    double perimeter = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dist(disks[i], disks[j]) <= disks[i].x + disks[j].x) {
                perimeter += 2 * M_PI * disks[i].x;
                perimeter += 2 * M_PI * disks[j].x;
                break;
            }
        }
    }

    printf("%.3f\n", perimeter);

    return 0;
}