#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1501

typedef struct {
    double x, y;
} Point;

Point polygon[MAXN];
int n;

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double area(Point *polygon, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        sum += crossProduct(polygon[i], polygon[j]);
    }
    return fabs(sum / 2);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    fscanf(input, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &polygon[i].x, &polygon[i].y);
    }
    double result = area(polygon, n);
    fprintf(output, "%.2lf\n", result);
    fclose(input);
    fclose(output);
    return 0;
}