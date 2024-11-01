#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 10000

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
Point temp[MAX_N];

int cmpX(const void* a, const void* b) {
    return ((Point*)a)->x - ((Point*)b)->x;
}

int cmpY(const void* a, const void* b) {
    return ((Point*)a)->y - ((Point*)b)->y;
}

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double stripClosest(Point strip[], int size, double d) {
    double min = d;
    qsort(strip, size, sizeof(Point), cmpY);

    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            double distance = dist(strip[i], strip[j]);
            if (distance < min)
                min = distance;
        }

    return min;
}

double closestUtil(Point P[], int n) {
    if (n <= 3) {
        double min = INFINITY;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                double distance = dist(P[i], P[j]);
                if (distance < min)
                    min = distance;
            }
        return min;
    }

    int mid = n / 2;
    Point midPoint = P[mid];

    double dl = closestUtil(P, mid);
    double dr = closestUtil(P + mid, n - mid);

    double d = dl < dr ? dl : dr;

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j++] = P[i];

    return fmin(d, stripClosest(strip, j, d));
}

double closest(Point P[], int n) {
    qsort(P, n, sizeof(Point), cmpX);
    return closestUtil(P, n);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    double result = closest(points, n);
    printf("%.4f\n", result);

    return 0;
}