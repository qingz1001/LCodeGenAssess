#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100005

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int N;

int manhattan_distance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int min_diff = INT_MAX;

    for (int i = 0; i < N; i++) {
        int distances[MAX_N];
        int count = 0;

        for (int j = 0; j < N; j++) {
            if (i != j) {
                distances[count++] = manhattan_distance(points[i], points[j]);
            }
        }

        qsort(distances, count, sizeof(int), compare);

        int diff = distances[count - 1] - distances[0];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    printf("%d\n", min_diff);

    return 0;
}