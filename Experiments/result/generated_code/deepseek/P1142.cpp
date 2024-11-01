#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int max(int a, int b) {
    return a > b ? a : b;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int comparePoints(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x) return p1->y - p2->y;
    return p1->x - p2->x;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), comparePoints);

    int maxPointsOnLine = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int count = 2;
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            int g = gcd(abs(dx), abs(dy));
            dx /= g;
            dy /= g;

            for (int k = j + 1; k < n; k++) {
                int dx2 = points[k].x - points[i].x;
                int dy2 = points[k].y - points[i].y;
                int g2 = gcd(abs(dx2), abs(dy2));
                dx2 /= g2;
                dy2 /= g2;

                if (dx == dx2 && dy == dy2) {
                    count++;
                }
            }

            maxPointsOnLine = max(maxPointsOnLine, count);
        }
    }

    printf("%d\n", maxPointsOnLine);

    return 0;
}