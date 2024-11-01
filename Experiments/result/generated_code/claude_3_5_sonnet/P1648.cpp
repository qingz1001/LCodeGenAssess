#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000
#define MAX_D 4
#define INF 0x3f3f3f3f

int n, d;
int points[MAX_N][MAX_D];
int min_coord[MAX_D], max_coord[MAX_D];

int main() {
    scanf("%d %d", &n, &d);

    memset(min_coord, 0x3f, sizeof(min_coord));
    memset(max_coord, 0, sizeof(max_coord));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i][j]);
            if (points[i][j] < min_coord[j]) min_coord[j] = points[i][j];
            if (points[i][j] > max_coord[j]) max_coord[j] = points[i][j];
        }
    }

    int max_distance = 0;
    for (int j = 0; j < d; j++) {
        max_distance += max_coord[j] - min_coord[j];
    }

    printf("%d\n", max_distance);

    return 0;
}