#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define EPSILON 1e-9

typedef struct {
    double x, y;
} Point;

int main() {
    int N;
    scanf("%d", &N);
    Point points[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    double sum_x = 0, sum_y = 0;
    for (int i = 0; i < N; i++) {
        sum_x += points[i].x;
        sum_y += points[i].y;
    }

    double center_x = sum_x / N;
    double center_y = sum_y / N;

    printf("V.I.P. should stay at (%.1f,%.1f).\n", center_x, center_y);

    return 0;
}