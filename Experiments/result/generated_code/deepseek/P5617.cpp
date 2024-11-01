#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double calculate_max_area(int n, int k, int r, int *x) {
    double area = 0.0;
    double circle_area = PI * r * r;

    // Sort the x coordinates to maximize the number of non-overlapping circles
    qsort(x, n, sizeof(int), compare);

    // Calculate the maximum area by selecting k non-overlapping circles
    for (int i = 0; i < k; i++) {
        area += circle_area;
    }

    return area;
}

int main() {
    int n, k, r;
    scanf("%d %d %d", &n, &k, &r);

    int *x = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    double result = calculate_max_area(n, k, r, x);
    printf("%.8f\n", result);

    free(x);
    return 0;
}