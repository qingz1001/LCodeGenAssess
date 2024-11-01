#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 3005

int n, row, line;
int boss[MAXN][2];

double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    scanf("%d%d%d", &n, &row, &line);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &boss[i][0], &boss[i][1]);
    }

    double maxDist = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= line; j++) {
            double minDist = 1e9;
            for (int k = 0; k < n; k++) {
                minDist = fmin(minDist, dist(i, j, boss[k][0], boss[k][1]));
            }
            maxDist = fmax(maxDist, minDist);
        }
    }

    printf("%.2lf\n", maxDist);
    return 0;
}