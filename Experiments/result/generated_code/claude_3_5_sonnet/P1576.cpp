#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 2001
#define MAX_M 100001

typedef struct {
    int x, y;
    double cost;
} Edge;

Edge edges[MAX_M];
double dist[MAX_N];
int n, m, A, B;

void bellman_ford() {
    for (int i = 1; i <= n; i++) {
        dist[i] = DBL_MAX;
    }
    dist[A] = 100.0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = edges[j].x;
            int y = edges[j].y;
            double cost = edges[j].cost;

            if (dist[x] != DBL_MAX && dist[y] > dist[x] * cost) {
                dist[y] = dist[x] * cost;
            }
            if (dist[y] != DBL_MAX && dist[x] > dist[y] * cost) {
                dist[x] = dist[y] * cost;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        edges[i].x = x;
        edges[i].y = y;
        edges[i].cost = 100.0 / (100.0 - z);
    }

    scanf("%d %d", &A, &B);

    bellman_ford();

    printf("%.8f\n", dist[B]);

    return 0;
}