#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double closest_pair(Point points[], int n) {
    if (n <= 3) {
        double min_dist = INFINITY;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = distance(points[i], points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        return min_dist;
    }

    qsort(points, n, sizeof(Point), compare);

    int mid = n / 2;
    Point mid_point = points[mid];

    double dl = closest_pair(points, mid);
    double dr = closest_pair(points + mid, n - mid);

    double d = fmin(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - mid_point.x) < d) {
            strip[j++] = points[i];
        }
    }

    for (int i = 0; i < j; i++) {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < d; k++) {
            double dist = distance(strip[i], strip[k]);
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    double result = closest_pair(points, n);
    printf("%.4f\n", result);

    return 0;
}