#include <stdio.h>
#include <math.h>

#define INF 1e9

typedef struct {
    double x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    int n, S, t, A, B;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d %d %d", &S, &t, &A, &B);
        Point airports[S][4];
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < 4; j++) {
                scanf("%lf %lf", &airports[i][j].x, &airports[i][j].y);
            }
        }

        double min_cost = INF;
        for (int ai = 0; ai < 4; ai++) {
            for (int bi = 0; bi < 4; bi++) {
                double cost = distance(airports[A-1][ai], airports[B-1][bi]);
                for (int ci = 0; ci < S; ci++) {
                    if (ci == A-1 || ci == B-1) continue;
                    for (int di = 0; di < 4; di++) {
                        cost += t * distance(airports[ci][di], airports[ci][(di+1)%4]) / 2;
                    }
                }
                min_cost = fmin(min_cost, cost);
            }
        }

        printf("%.1f\n", min_cost);
    }
    return 0;
}