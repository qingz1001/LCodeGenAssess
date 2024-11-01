#include <stdio.h>
#include <math.h>

#define MAX_N 1500

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int n;

double calculateArea(Point p1, Point p2, Point p3) {
    return fabs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) / 2.0;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fscanf(input, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d %d", &points[i].x, &points[i].y);
    }

    double total_area = 0;
    double shaded_area = 0;

    for (int i = 1; i < n - 1; i++) {
        total_area += calculateArea(points[0], points[i], points[i + 1]);
    }

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (i + 2) % n;
        shaded_area += calculateArea(points[i], points[j], points[k]);
    }

    double result = total_area - shaded_area;
    fprintf(output, "%.2f\n", result);

    fclose(input);
    fclose(output);
    return 0;
}