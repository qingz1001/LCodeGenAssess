#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 5001

struct Point {
    int x, y;
};

struct Point points[MAXN];

int compare(const void *a, const void *b) {
    struct Point *pointA = (struct Point *)a;
    struct Point *pointB = (struct Point *)b;
    if (pointA->x != pointB->x) {
        return pointA->x - pointB->x;
    } else {
        return pointA->y - pointB->y;
    }
}

double calculateY(int i, int j, int k) {
    double m1 = (double)(points[j].y - points[i].y) / (points[j].x - points[i].x);
    double m2 = (double)(points[k].y - points[j].y) / (points[k].x - points[j].x);
    return (m1 * points[j].x + m2 * points[i].x - m2 * points[j].x - m1 * points[i].x) / (m1 - m2);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(struct Point), compare);

    double min_y = 1e9;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                double y = calculateY(i, j, k);
                if (y < min_y) {
                    min_y = y;
                }
            }
        }
    }

    printf("%.2lf\n", min_y);
    return 0;
}