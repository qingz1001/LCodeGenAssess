#include <stdio.h>
#include <stdlib.h>

#define MAX_N 700

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int n;

int compare(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    int max_points = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            int g = gcd(abs(dx), abs(dy));
            dx /= g;
            dy /= g;

            int count = 2;
            for (int k = j + 1; k < n; k++) {
                int dx2 = points[k].x - points[i].x;
                int dy2 = points[k].y - points[i].y;
                if (dx * dy2 == dy * dx2) {
                    count++;
                }
            }
            if (count > max_points) {
                max_points = count;
            }
        }
    }

    printf("%d\n", max_points);
    return 0;
}