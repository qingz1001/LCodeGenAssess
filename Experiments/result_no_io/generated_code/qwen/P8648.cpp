#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_X 10005
#define MAX_Y 10005

int main() {
    int n;
    scanf("%d", &n);
    int grid[MAX_X][MAX_Y] = {0};

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int j = x1; j <= x2; ++j) {
            for (int k = y1; k <= y2; ++k) {
                grid[j][k]++;
            }
        }
    }

    int total_area = 0;
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            if (grid[i][j] > 0) {
                total_area++;
            }
        }
    }

    printf("%d\n", total_area);

    return 0;
}