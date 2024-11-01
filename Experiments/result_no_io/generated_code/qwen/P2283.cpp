#include <stdio.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

double crossProduct(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

double polygonArea(int n, Point points[]) {
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += crossProduct(points[0], points[i], points[j]);
    }
    return fabs(area / 2.0);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output) {
        printf("Error opening files\n");
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    Point points[n];
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }

    double area = polygonArea(n, points);
    fprintf(output, "%.2f\n", area);

    fclose(input);
    fclose(output);

    return 0;
}