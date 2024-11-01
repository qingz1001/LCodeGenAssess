#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
#define MAX_COORD 10000

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int C, N;

int compare(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

int count_points(int x1, int y1, int size) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (points[i].x >= x1 && points[i].x <= x1 + size &&
            points[i].y >= y1 && points[i].y <= y1 + size) {
            count++;
        }
    }
    return count;
}

int solve() {
    int min_size = 10000;
    qsort(points, N, sizeof(Point), compare);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x1 = points[i].x;
            int y1 = points[j].y;
            int left = 0, right = 10000;

            while (left <= right) {
                int mid = (left + right) / 2;
                if (count_points(x1, y1, mid) >= C) {
                    min_size = (min_size < mid) ? min_size : mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }
    }

    return min_size;
}

int main() {
    scanf("%d %d", &C, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    printf("%d\n", solve());
    return 0;
}