#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

typedef struct {
    int count;
    int last_round;
} PointInfo;

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    PointInfo grid[MAX_N][MAX_M] = {0};

    for (int i = 0; i < x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int row = x1 - 1; row < x2; row++) {
            for (int col = y1 - 1; col < y2; col++) {
                grid[row][col].count++;
                grid[row][col].last_round = i + 1;
            }
        }
    }

    for (int i = 0; i < y; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        px--; py--;
        if (grid[px][py].count > 0) {
            printf("Y %d %d\n", grid[px][py].count, grid[px][py].last_round);
        } else {
            printf("N\n");
        }
    }

    return 0;
}