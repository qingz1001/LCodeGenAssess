#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAXN 150
#define INF DBL_MAX

typedef struct {
    int x, y;
} Point;

int N;
Point points[MAXN];
double dist[MAXN][MAXN];
double max_dist[MAXN];

double distance(Point a, Point b) {
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int connected;
            scanf("%1d", &connected);
            if (connected) {
                dist[i][j] = distance(points[i], points[j]);
            } else if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    floyd_warshall();

    double min_diameter = INF;
    double max_in_field = 0;

    for (int i = 0; i < N; i++) {
        max_dist[i] = 0;
        for (int j = 0; j < N; j++) {
            if (dist[i][j] != INF) {
                max_dist[i] = fmax(max_dist[i], dist[i][j]);
            }
        }
        max_in_field = fmax(max_in_field, max_dist[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF) {
                double new_diameter = max_dist[i] + max_dist[j] + distance(points[i], points[j]);
                min_diameter = fmin(min_diameter, new_diameter);
            }
        }
    }

    printf("%.6f\n", fmax(min_diameter, max_in_field));

    return 0;
}