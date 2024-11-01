#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define EPS 1e-6

typedef struct {
    int h;
    double r1, r2;
} Bowl;

double min(double a, double b) {
    return a < b ? a : b;
}

int compare(const void *a, const void *b) {
    Bowl *x = (Bowl *)a;
    Bowl *y = (Bowl *)b;
    if (x->r2 / x->r1 - y->r2 / y->r1 > EPS) return 1;
    if (x->r2 / x->r1 - y->r2 / y->r1 < -EPS) return -1;
    return 0;
}

double calculate_height(Bowl bowls[], int n) {
    double height = 0.0;
    for (int i = 0; i < n; i++) {
        height += bowls[i].h;
    }
    return height;
}

int main() {
    int n;
    scanf("%d", &n);
    Bowl bowls[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %lf %lf", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }

    qsort(bowls, n, sizeof(Bowl), compare);

    printf("%.0f\n", calculate_height(bowls, n));

    return 0;
}