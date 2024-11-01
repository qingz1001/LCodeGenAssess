#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005
#define MAXD 5

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    int **points = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        points[i] = (int *)malloc(d * sizeof(int));
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i][j]);
        }
    }

    int maxDistance = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int distance = 0;
            for (int k = 0; k < d; k++) {
                distance += abs(points[i][k] - points[j][k]);
            }
            if (distance > maxDistance) {
                maxDistance = distance;
            }
        }
    }

    printf("%d\n", maxDistance);

    for (int i = 0; i < n; i++) {
        free(points[i]);
    }
    free(points);

    return 0;
}