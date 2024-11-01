#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_COORD 2 * 10000 + 1

int main() {
    int N;
    scanf("%d", &N);

    int x[MAX_N][2];
    int y[MAX_N][2];

    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
    }

    int minX = x[0][0], maxX = x[0][1];
    int minY = y[0][0], maxY = y[0][1];

    for (int i = 1; i < N; ++i) {
        if (x[i][0] < minX) minX = x[i][0];
        if (x[i][1] > maxX) maxX = x[i][1];
        if (y[i][0] < minY) minY = y[i][0];
        if (y[i][1] > maxY) maxY = y[i][1];
    }

    int perimeter = 2 * (maxX - minX + maxY - minY);
    printf("%d\n", perimeter);

    return 0;
}