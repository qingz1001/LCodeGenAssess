#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int main() {
    int N;
    scanf("%d", &N);
    int x1, y1, x2, y2;
    int holes[MAX_N][MAX_N] = {0};
    int max_x = -1000, min_x = 1000, max_y = -1000, min_y = 1000;

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            if (y1 > y2) {
                int temp = y1;
                y1 = y2;
                y2 = temp;
            }
            for (int j = y1; j <= y2; j++) {
                holes[x1][j]++;
            }
        } else {
            if (x1 > x2) {
                int temp = x1;
                x1 = x2;
                x2 = temp;
            }
            for (int j = x1; j <= x2; j++) {
                holes[j][y1]++;
            }
        }
        if (x1 > max_x) max_x = x1;
        if (x2 > max_x) max_x = x2;
        if (y1 > max_y) max_y = y1;
        if (y2 > max_y) max_y = y2;
        if (x1 < min_x) min_x = x1;
        if (x2 < min_x) min_x = x2;
        if (y1 < min_y) min_y = y1;
        if (y2 < min_y) min_y = y2;
    }

    int count = 0;
    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            if (holes[i][j] == 1) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}