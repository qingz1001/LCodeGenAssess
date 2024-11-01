#include <stdio.h>
#include <stdlib.h>
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

double euclidean_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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
            scanf("%d", &connected);
            if (connected) {
                dist[i][j] = euclidean_distance(points[i], points[j]);
            } else if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    floyd_warshall();

    double max_diameter = 0;
    for (int i = 0; i < N; i++) {
        max_dist[i] = 0;
        for (int j = 0; j < N; j++) {
            if (dist[i][j] != INF) {
                max_dist[i] = fmax(max_dist[i], dist[i][j]);
            }
        }
        max_diameter = fmax(max_diameter, max_dist[i]);
    }

    double min_new_diameter = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF) {
                double new_diameter = max_dist[i] + max_dist[j] + euclidean_distance(points[i], points[j]);
                min_new_diameter = fmin(min_new_diameter, new_diameter);
            }
        }
    }

    printf("%.6f\n", fmax(max_diameter, min_new_diameter));

    return 0;
}