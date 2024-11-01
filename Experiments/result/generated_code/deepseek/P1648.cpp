#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000000
#define MAXD 4

int points[MAXN][MAXD];

int max(int a, int b) {
    return a > b ? a : b;
}

int abs(int x) {
    return x > 0 ? x : -x;
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i][j]);
        }
    }

    int max_distance = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int distance = 0;
            for (int k = 0; k < d; k++) {
                distance += abs(points[i][k] - points[j][k]);
            }
            max_distance = max(max_distance, distance);
        }
    }

    printf("%d\n", max_distance);

    return 0;
}