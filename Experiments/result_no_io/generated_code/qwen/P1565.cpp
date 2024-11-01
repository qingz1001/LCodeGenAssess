#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int n, m;
int grid[MAX_N][MAX_M];
int prefix_sum[MAX_N + 1][MAX_M + 1];

int max_rectangle_area() {
    int max_area = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefix_sum[i + 1][j + 1] = prefix_sum[i][j + 1] + prefix_sum[i + 1][j] - prefix_sum[i][j] + grid[i][j];
        }
    }

    for (int y1 = 0; y1 < n; y1++) {
        for (int y2 = y1; y2 < n; y2++) {
            for (int x1 = 0; x1 < m; x1++) {
                for (int x2 = x1; x2 < m; x2++) {
                    int area = (prefix_sum[y2 + 1][x2 + 1] - prefix_sum[y2 + 1][x1] - prefix_sum[y1][x2 + 1] + prefix_sum[y1][x1]);
                    if (area > 0) {
                        max_area = fmax(max_area, area);
                    }
                }
            }
        }
    }

    return max_area;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    printf("%d\n", max_rectangle_area());

    return 0;
}