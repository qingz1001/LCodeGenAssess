#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 800
#define MAX_N 1000

typedef struct {
    int x;
    int y;
} Tower;

int compareTowers(const void *a, const void *b) {
    Tower *t1 = (Tower *)a;
    Tower *t2 = (Tower *)b;
    return t1->x - t2->x;
}

int canCover(Tower *towers, int m, double radius) {
    double max_right = 0;
    for (int i = 0; i < m; i++) {
        if (towers[i].x - radius > max_right) {
            return 0;
        }
        double right = towers[i].x + sqrt(radius * radius - towers[i].y * towers[i].y);
        if (right > max_right) {
            max_right = right;
        }
    }
    return max_right >= MAX_N;
}

double binarySearch(Tower *towers, int m) {
    double left = 0, right = 1e10;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        if (canCover(towers, m, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    int N, M;
    Tower towers[MAX_M];

    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }

    qsort(towers, M, sizeof(Tower), compareTowers);

    double result = binarySearch(towers, M);
    printf("%.2f\n", result);

    return 0;
}