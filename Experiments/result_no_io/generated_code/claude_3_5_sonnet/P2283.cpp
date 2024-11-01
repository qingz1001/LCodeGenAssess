#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1500

typedef struct {
    int x, y;
} Point;

double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double triangle_area(Point a, Point b, Point c) {
    return fabs(cross_product(a, b, c)) / 2.0;
}

double polygon_area(Point* points, int n) {
    double area = 0.0;
    for (int i = 1; i < n - 1; i++) {
        area += triangle_area(points[0], points[i], points[i+1]);
    }
    return area;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    Point points[MAX_N];
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d %d", &points[i].x, &points[i].y);
    }
    
    double total_area = polygon_area(points, n);
    double shaded_area = 0.0;
    
    for (int i = 0; i < n; i++) {
        int j = (i + 2) % n;
        shaded_area += triangle_area(points[i], points[(i+1)%n], points[j]);
    }
    
    fprintf(output, "%.2f\n", shaded_area);
    
    fclose(input);
    fclose(output);
    return 0;
}