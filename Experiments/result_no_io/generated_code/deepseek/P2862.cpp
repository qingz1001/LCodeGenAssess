#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_COORD 10000

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int C, N;
    scanf("%d %d", &C, &N);

    Point points[MAX_N];
    int x_coords[MAX_N], y_coords[MAX_N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        x_coords[i] = points[i].x;
        y_coords[i] = points[i].y;
    }

    qsort(x_coords, N, sizeof(int), compare);
    qsort(y_coords, N, sizeof(int), compare);

    int prefix_sum[MAX_N + 1][MAX_N + 1] = {0};

    for (int i = 0; i < N; i++) {
        int x_index = (int)(bsearch(&points[i].x, x_coords, N, sizeof(int), compare) - x_coords);
        int y_index = (int)(bsearch(&points[i].y, y_coords, N, sizeof(int), compare) - y_coords);
        prefix_sum[x_index + 1][y_index + 1] = 1;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            prefix_sum[i][j] += prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1];
        }
    }

    int min_side = MAX_COORD;

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = k; l < N; l++) {
                    int count = prefix_sum[j + 1][l + 1] - prefix_sum[i][l + 1] - prefix_sum[j + 1][k] + prefix_sum[i][k];
                    if (count >= C) {
                        int side = x_coords[j] - x_coords[i] > y_coords[l] - y_coords[k] ? x_coords[j] - x_coords[i] : y_coords[l] - y_coords[k];
                        if (side < min_side) {
                            min_side = side;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", min_side + 1);

    return 0;
}