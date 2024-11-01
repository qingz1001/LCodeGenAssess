#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double calculate_area(int r) {
    return PI * r * r;
}

int main() {
    int n, k, r;
    scanf("%d %d %d", &n, &k, &r);
    int *x = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    qsort(x, n, sizeof(int), compare);

    double total_area = 0.0;
    for (int i = 0; i < k; i++) {
        total_area += calculate_area(r);
    }

    printf("%.10f\n", total_area);

    free(x);
    return 0;
}