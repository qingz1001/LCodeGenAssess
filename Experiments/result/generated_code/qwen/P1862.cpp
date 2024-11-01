#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int x, y;
} Well;

int compare(const void *a, const void *b) {
    return ((Well *)a)->x - ((Well *)b)->x;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double distance(Well w, double x) {
    return abs(w.x - x);
}

int main() {
    int n;
    scanf("%d", &n);

    Well wells[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &wells[i].x, &wells[i].y);
    }

    qsort(wells, n, sizeof(Well), compare);

    double total_length = 0.0;
    for (int i = 0; i < n; ++i) {
        total_length += distance(wells[i], (wells[0].x + wells[n-1].x) / 2.0);
    }

    printf("%.0f\n", total_length);

    return 0;
}