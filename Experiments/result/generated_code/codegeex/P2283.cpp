#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x) return p1->y < p2->y ? -1 : 1;
    return p1->x < p2->x ? -1 : 1;
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double area(Point *points, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += crossProduct(points[i], points[(i + 1) % n]);
    }
    return fabs(sum) / 2.0;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);
    Point *points = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf", &points[i].x, &points[i].y);
    }

    qsort(points, n, sizeof(Point), compare);

    Point *newPoints = (Point *)malloc(2 * n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        newPoints[i] = points[i];
        newPoints[i + n] = points[i];
    }

    double totalArea = 0;
    for (int i = 0; i < n; i++) {
        totalArea += area(newPoints + i, n);
    }

    fprintf(output, "%.2lf\n", totalArea);
    fclose(input);
    fclose(output);
    free(points);
    free(newPoints);

    return 0;
}