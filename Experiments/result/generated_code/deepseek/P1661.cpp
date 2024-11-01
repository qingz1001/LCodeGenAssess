#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int distances[n * (n - 1) / 2];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            distances[idx++] = (int)ceil(sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2)));
        }
    }

    qsort(distances, idx, sizeof(int), compare);

    printf("%d\n", distances[0]);

    return 0;
}