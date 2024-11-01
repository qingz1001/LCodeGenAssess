#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

typedef struct {
    double x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int can_connect_all(Point *points, int n, int s, double d) {
    // Check if all points are connected with the given distance d
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i < s && j < s) { // Both points have satellite phones
                if (distance(points[i], points[j]) > d) {
                    return 0;
                }
            } else if (!(i < s && j < s)) { // At least one point does not have a satellite phone
                if (distance(points[i], points[j]) > d) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

double find_min_distance(Point *points, int n, int s) {
    double left = 0, right = 10000;
    while (right - left > EPSILON) {
        double mid = (left + right) / 2;
        if (can_connect_all(points, n, s, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    int s, p;
    scanf("%d %d", &s, &p);
    Point points[p];
    for (int i = 0; i < p; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    double min_distance = find_min_distance(points, p, s);
    printf("%.2f\n", min_distance);
    return 0;
}