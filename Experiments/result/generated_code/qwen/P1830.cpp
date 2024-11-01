#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100
#define MAX_X 100
#define MAX_Y 100

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    int bombed[MAX_N][MAX_M] = {0};
    int last_bombed[MAX_N][MAX_M] = {0};

    for (int i = 0; i < x; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int j = x1 - 1; j <= x2 - 1; ++j) {
            for (int k = y1 - 1; k <= y2 - 1; ++k) {
                bombed[j][k]++;
                last_bombed[j][k] = i + 1;
            }
        }
    }

    for (int i = 0; i < y; ++i) {
        int px, py;
        scanf("%d %d", &px, &py);
        if (bombed[px - 1][py - 1] > 0) {
            printf("Y %d %d\n", bombed[px - 1][py - 1], last_bombed[px - 1][py - 1]);
        } else {
            printf("N\n");
        }
    }

    return 0;
}