#include <stdio.h>
#include <stdlib.h>

#define MAXN 700

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

int maxPointsOnLine(Point points[], int n) {
    if (n <= 1) return n;

    int max_points = 0;

    for (int i = 0; i < n; i++) {
        qsort(points, n, sizeof(Point), compare);
        int same = 1;
        int vertical = 0;
        int horizontal = 0;
        double slope[2 * n];

        for (int j = i + 1; j < n; j++) {
            if (points[j].x == points[i].x && points[j].y == points[i].y) {
                same++;
            } else if (points[j].x == points[i].x) {
                vertical++;
            } else if (points[j].y == points[i].y) {
                horizontal++;
            } else {
                double m = (double)(points[j].y - points[i].y) / (points[j].x - points[i].x);
                int index = 0;
                while (index < j - i - 1 && slope[index] != m) {
                    index++;
                }
                if (index == j - i - 1) {
                    slope[index] = m;
                }
            }
        }

        int current_max = same + vertical + horizontal + 1;
        for (int k = 0; k < j - i - 1; k++) {
            current_max = current_max > same + k + 1 ? current_max : same + k + 1;
        }

        max_points = max_points > current_max ? max_points : current_max;
    }

    return max_points;
}

int main() {
    int n;
    scanf("%d", &n);

    Point points[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    printf("%d\n", maxPointsOnLine(points, n));

    return 0;
}