#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

typedef struct {
    int x, h;
} Point;

Point points[MAX_M];
int n, m;

int cmp(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pb->h - pa->h;
}

void add_point(int x, int h) {
    points[m].x = x;
    points[m].h = h;
    m++;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int h, l, r;
        scanf("%d %d %d", &h, &l, &r);
        add_point(l, h);
        add_point(r, -h);
    }

    qsort(points, m, sizeof(Point), cmp);

    int height[MAX_M] = {0};
    int size = 0;
    int prev_height = 0;
    int result[MAX_M][2], result_size = 0;

    for (int i = 0; i < m; i++) {
        if (points[i].h > 0) {
            height[size++] = points[i].h;
        } else {
            for (int j = 0; j < size; j++) {
                if (height[j] == -points[i].h) {
                    memmove(&height[j], &height[j+1], (size-j-1) * sizeof(int));
                    size--;
                    break;
                }
            }
        }

        int max_height = 0;
        for (int j = 0; j < size; j++) {
            if (height[j] > max_height) max_height = height[j];
        }

        if (max_height != prev_height) {
            result[result_size][0] = points[i].x;
            result[result_size][1] = max_height;
            result_size++;
            prev_height = max_height;
        }
    }

    printf("%d\n", result_size);
    for (int i = 0; i < result_size; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }

    return 0;
}