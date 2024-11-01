#include <stdio.h>
#include <math.h>

#define MAX_M 800
#define MAX_N 1000
#define EPS 1e-6

typedef struct {
    int x, y;
} Point;

Point towers[MAX_M + 1];
int N, M;

double check(double r) {
    double left = 0, right = N;
    for (int i = 1; i <= M; i++) {
        double d = sqrt(r * r - towers[i].y * towers[i].y);
        double l = towers[i].x - d;
        double r = towers[i].x + d;
        if (l <= left && r >= right) return 1;
        if (r > left) left = r;
    }
    return left >= right;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }

    double low = 0, high = 1e6;
    while (high - low > EPS) {
        double mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }

    printf("%.2f\n", low);
    return 0;
}