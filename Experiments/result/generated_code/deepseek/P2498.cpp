#include <stdio.h>
#include <math.h>

#define MAXN 3000

typedef struct {
    int x, y;
} Point;

Point bosses[MAXN];

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    int n, row, line;
    scanf("%d %d %d", &n, &row, &line);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bosses[i].x, &bosses[i].y);
    }

    double left = 0.0, right = min(row, line);
    double eps = 1e-6;

    while (right - left > eps) {
        double mid = (left + right) / 2.0;
        int canReach = 0;

        for (int i = 0; i < n; i++) {
            if (bosses[i].x - mid <= 1 || bosses[i].y - mid <= 1 ||
                bosses[i].x + mid >= row || bosses[i].y + mid >= line) {
                canReach = 1;
                break;
            }
        }

        if (canReach) {
            right = mid;
        } else {
            left = mid;
        }
    }

    printf("%.2f\n", left);

    return 0;
}