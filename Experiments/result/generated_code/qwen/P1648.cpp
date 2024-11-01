#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_D 4

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    int points[MAX_N][MAX_D];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i][j]);
        }
    }

    // Sort each dimension separately
    for (int j = 0; j < d; j++) {
        qsort(points[0], n, sizeof(int), compare);
    }

    int max_distance = 0;
    for (int i = 0; i < n - 1; i++) {
        int distance = 0;
        for (int j = 0; j < d; j++) {
            distance += abs(points[i][j] - points[i + 1][j]);
        }
        if (distance > max_distance) {
            max_distance = distance;
        }
    }

    printf("%d\n", max_distance);

    return 0;
}