#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9

typedef struct {
    int x, y;
} Point;

int n;
Point cities[5005];
double dist[5005][5005];

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].x, &cities[i].y);
        for (int j = 0; j < n; j++) {
            dist[i][j] = distance(cities[i], cities[j]);
        }
    }

    floyd();

    double total_length = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist[i][j] != INF && dist[i][j] < total_length) {
                total_length += dist[i][j];
            }
        }
    }

    printf("%.2f\n", total_length);

    return 0;
}