#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_COORD 10000

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x) return p1->y - p2->y;
    return p1->x - p2->x;
}

int main() {
    int C, N;
    scanf("%d %d", &C, &N);

    Point points[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    int min_side = MAX_COORD;

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int x_min = points[i].x;
            int x_max = points[j].x;
            if (x_max - x_min >= min_side) break;

            int y_values[MAX_N];
            int k = 0;
            for (int l = i; l <= j; l++) {
                y_values[k++] = points[l].y;
            }

            qsort(y_values, k, sizeof(int), compare);

            for (int m = 0; m < k; m++) {
                for (int n = m; n < k; n++) {
                    int y_min = y_values[m];
                    int y_max = y_values[n];
                    if (y_max - y_min >= min_side) break;

                    int count = 0;
                    for (int l = i; l <= j; l++) {
                        if (points[l].y >= y_min && points[l].y <= y_max) {
                            count++;
                        }
                    }

                    if (count >= C) {
                        int side = x_max - x_min > y_max - y_min ? x_max - x_min : y_max - y_min;
                        if (side < min_side) {
                            min_side = side;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", min_side + 1);

    return 0;
}