#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x[4];
} Point;

long long maxDistance(Point* points, int n) {
    long long maxDist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dist = 0;
            for (int k = 0; k < 4; k++) {
                dist += abs(points[i].x[k] - points[j].x[k]);
            }
            if (dist > maxDist) {
                maxDist = dist;
            }
        }
    }
    return maxDist;
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    Point* points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%lld", &points[i].x[j]);
        }
    }

    long long result = maxDistance(points, n);
    printf("%lld\n", result);

    free(points);
    return 0;
}