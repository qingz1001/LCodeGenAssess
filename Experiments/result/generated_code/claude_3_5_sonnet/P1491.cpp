#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 200
#define MAX_M 10000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

Point points[MAX_N + 1];
Edge edges[MAX_M];
int n, m;
double dist[MAX_N + 1][MAX_N + 1];
double shortest[MAX_N + 1];
double second_shortest[MAX_N + 1];

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void dijkstra() {
    int visited[MAX_N + 1] = {0};
    for (int i = 1; i <= n; i++) {
        shortest[i] = DBL_MAX;
        second_shortest[i] = DBL_MAX;
    }
    shortest[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        double min_dist = DBL_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && shortest[j] < min_dist) {
                u = j;
                min_dist = shortest[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (dist[u][v] != DBL_MAX) {
                double new_dist = shortest[u] + dist[u][v];
                if (new_dist < shortest[v]) {
                    second_shortest[v] = shortest[v];
                    shortest[v] = new_dist;
                } else if (new_dist < second_shortest[v] && new_dist != shortest[v]) {
                    second_shortest[v] = new_dist;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = DBL_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        double d = calculate_distance(points[u], points[v]);
        dist[u][v] = d;
        dist[v][u] = d;
    }

    dijkstra();

    if (second_shortest[n] == DBL_MAX) {
        printf("-1\n");
    } else {
        printf("%.2f\n", second_shortest[n]);
    }

    return 0;
}