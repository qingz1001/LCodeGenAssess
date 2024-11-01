#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000000
#define MAX_D 4

int n, d;
int points[MAX_N][MAX_D];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &d);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i][j]);
        }
    }

    int max_dist = 0;
    int min_coords[MAX_D], max_coords[MAX_D];

    for (int j = 0; j < d; j++) {
        min_coords[j] = INT_MAX;
        max_coords[j] = INT_MIN;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            min_coords[j] = min(min_coords[j], points[i][j]);
            max_coords[j] = max(max_coords[j], points[i][j]);
        }
    }

    for (int j = 0; j < d; j++) {
        max_dist += max_coords[j] - min_coords[j];
    }

    printf("%d\n", max_dist);

    return 0;
}