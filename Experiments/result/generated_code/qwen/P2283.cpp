#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

typedef struct {
    double x, y;
} Point;

double crossProduct(Point p1, Point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

double polygonArea(int n, Point points[]) {
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += crossProduct(points[i], points[j]);
    }
    return fabs(area / 2.0);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output) {
        printf("Failed to open files\n");
        return 1;
    }

    int N;
    fscanf(input, "%d", &N);

    Point points[N];
    for (int i = 0; i < N; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }

    double area = polygonArea(N, points);

    fprintf(output, "%.2f\n", area);

    fclose(input);
    fclose(output);

    return 0;
}