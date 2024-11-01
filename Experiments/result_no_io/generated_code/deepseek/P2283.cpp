#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

double calculateArea(Point polygon[], int n) {
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y;
    }
    return area / 2.0;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error opening files.\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    Point *polygon = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &polygon[i].x, &polygon[i].y);
    }

    double area = calculateArea(polygon, n);
    fprintf(outputFile, "%.2f\n", area);

    free(polygon);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}