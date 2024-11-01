#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50005
#define MAX_XY 1003

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);

    int x[MAX_N], y[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    int count = 0;

    // Move to the origin by moving along the axes
    while (x0 != 0 || y0 != 0) {
        if (x0 > 0) {
            x0--;
        } else if (x0 < 0) {
            x0++;
        }
        if (y0 > 0) {
            y0--;
        } else if (y0 < 0) {
            y0++;
        }
        count++;
    }

    printf("%d\n", count);

    return 0;
}