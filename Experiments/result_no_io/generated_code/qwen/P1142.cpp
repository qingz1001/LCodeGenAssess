#include <stdio.h>
#include <stdlib.h>

#define MAXN 705

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

int maxPointsOnLine(Point points[], int n) {
    if (n <= 2) return n;

    int max_points = 0;

    for (int i = 0; i < n; i++) {
        int same = 1;
        int vertical = 0;
        int slopes[360] = {0};

        for (int j = i + 1; j < n; j++) {
            if (points[i].x == points[j].x) {
                if (points[i].y == points[j].y) {
                    same++;
                } else {
                    vertical++;
                }
            } else {
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                int gcd = __gcd(abs(dx), abs(dy));
                dx /= gcd;
                dy /= gcd;
                int angle = (dy * 180 + dx / 2) % 360;
                slopes[angle]++;
            }
        }

        int current_max = same;
        for (int k = 0; k < 360; k++) {
            if (slopes[k] > current_max) {
                current_max = slopes[k];
            }
        }

        max_points = (max_points > current_max + vertical + same) ? max_points : current_max + vertical + same;
    }

    return max_points;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAXN];

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    printf("%d\n", maxPointsOnLine(points, n));

    return 0;
}