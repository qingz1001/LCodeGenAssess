#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x < p2->x)
        return -1;
    else if (p1->x > p2->x)
        return 1;
    else
        return 0;
}

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point points[], int start, int end) {
    double minDist = 9999999999.0;
    for (int i = start; i < end; i++) {
        for (int j = i + 1; j <= end; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

double stripClosest(Point strip[], int size, double d) {
    double minDist = d;
    qsort(strip, size, sizeof(Point), compare);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

double closestUtil(Point points[], int n) {
    if (n <= 3) {
        return bruteForce(points, 0, n - 1);
    }
    int mid = n / 2;
    Point midPoint = points[mid];
    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);
    double d = (dl < dr) ? dl : dr;
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[j] = points[i];
            j++;
        }
    }
    return stripClosest(strip, j, d);
}

double closestPair(Point points[], int n) {
    qsort(points, n, sizeof(Point), compare);
    return closestUtil(points, n);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    printf("%.4lf\n", closestPair(points, n));
    return 0;
}