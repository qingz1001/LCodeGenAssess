#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int compare(const void *a, const void *b) {
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

    int max_points = 0;
    for (int i = 0; i < n; i++) {
        Point slopes[n];
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            int g = gcd(dx, dy);
            slopes[count].x = dx / g;
            slopes[count].y = dy / g;
            count++;
        }

        qsort(slopes, count, sizeof(Point), compare);

        int current_count = 1;
        for (int j = 1; j < count; j++) {
            if (slopes[j].x == slopes[j - 1].x && slopes[j].y == slopes[j - 1].y) {
                current_count++;
            } else {
                if (current_count > max_points) {
                    max_points = current_count;
                }
                current_count = 1;
            }
        }
        if (current_count > max_points) {
            max_points = current_count;
        }
    }

    printf("%d\n", max_points + 1);
    return 0;
}