#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 3005

int n, row, line;
int boss[MAXN][2];

double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double maxDistance() {
    double maxDist = 0.0;
    for (int i = 1; i <= n; i++) {
        double currentDist = dist(1, 1, boss[i][0], boss[i][1]);
        if (currentDist > maxDist) {
            maxDist = currentDist;
        }
    }
    return maxDist;
}

int main() {
    scanf("%d %d %d", &n, &row, &line);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &boss[i][0], &boss[i][1]);
    }
    double result = maxDistance();
    printf("%.2f\n", result);
    return 0;
}