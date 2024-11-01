#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define INF 1e9

typedef struct {
    double x, y;
} Point;

double dirt_cost, rome_cost;
int N;
Point points[MAX_N];
int rome_road[MAX_N][MAX_N];
Point dock, home;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dijkstra(int start, int end) {
    double dist[MAX_N];
    int visited[MAX_N];
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < N - 1; count++) {
        double min_dist = INF;
        int u = -1;
        for (int v = 0; v < N; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < N; v++) {
            if (!visited[v]) {
                double cost = rome_road[u][v] ? rome_cost * distance(points[u], points[v]) : dirt_cost * distance(points[u], points[v]);
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                }
            }
        }
    }
    return dist[end];
}

int main() {
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rome_road[i][j] = 0;
        }
    }
    int i, j;
    while (scanf("%d %d", &i, &j) == 2 && (i != 0 || j != 0)) {
        rome_road[i-1][j-1] = rome_road[j-1][i-1] = 1;
    }
    scanf("%lf %lf", &dock.x, &dock.y);
    scanf("%lf %lf", &home.x, &home.y);

    int dock_index = N, home_index = N + 1;
    points[dock_index] = dock;
    points[home_index] = home;
    N += 2;

    double min_unhappiness = INF;
    for (int i = 0; i < N - 2; i++) {
        for (int j = 0; j < N - 2; j++) {
            if (rome_road[i][j]) {
                double unhappiness = dijkstra(dock_index, i) + rome_cost * distance(points[i], points[j]) + dijkstra(j, home_index);
                if (unhappiness < min_unhappiness) {
                    min_unhappiness = unhappiness;
                }
            }
        }
    }

    printf("%.4lf\n", min_unhappiness);
    return 0;
}