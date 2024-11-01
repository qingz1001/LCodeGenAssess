#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9

typedef struct {
    int x[4];
    int y[4];
    int T;
} City;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int S, t, A, B;
        scanf("%d %d %d %d", &S, &t, &A, &B);

        City cities[S];
        for (int i = 0; i < S; i++) {
            scanf("%d %d %d %d %d %d %d",
                  &cities[i].x[0], &cities[i].y[0],
                  &cities[i].x[1], &cities[i].y[1],
                  &cities[i].x[2], &cities[i].y[2],
                  &cities[i].T);
        }

        double min_cost = INF;
        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4; b++) {
                double cost = distance(cities[A-1].x[a], cities[A-1].y[a], cities[B-1].x[b], cities[B-1].y[b]);
                if (cost == 0) {
                    cost = cities[A-1].T * distance(cities[A-1].x[(a+1)%4], cities[A-1].y[(a+1)%4], cities[B-1].x[b], cities[B-1].y[b]);
                }
                cost += t * (distance(0, 0, cities[A-1].x[a], cities[A-1].y[a]) +
                             distance(0, 0, cities[B-1].x[b], cities[B-1].y[b]));
                min_cost = fmin(min_cost, cost);
            }
        }

        printf("%.1f\n", min_cost);
    }
    return 0;
}