#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000
#define INF 1e9

typedef struct {
    double x, y;
} Point;

double dirt_cost, rome_cost;
int N;
Point points[MAXN];
int rome_roads[MAXN][MAXN];
Point dock, home;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dijkstra(int start, int end) {
    double cost[MAXN];
    int visited[MAXN];
    for (int i = 0; i < N; i++) {
        cost[i] = INF;
        visited[i] = 0;
    }
    cost[start] = 0;

    for (int count = 0; count < N - 1; count++) {
        double min_cost = INF;
        int min_index = -1;
        for (int i = 0; i < N; i++) {
            if (!visited[i] && cost[i] < min_cost) {
                min_cost = cost[i];
                min_index = i;
            }
        }
        if (min_index == -1) break;
        visited[min_index] = 1;

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                double d = dist(points[min_index], points[i]);
                double new_cost = cost[min_index] + (rome_roads[min_index][i] ? rome_cost : dirt_cost) * d;
                if (new_cost < cost[i]) {
                    cost[i] = new_cost;
                }
            }
        }
    }

    return cost[end];
}

int main() {
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rome_roads[i][j] = 0;
        }
    }

    int i, j;
    while (scanf("%d %d", &i, &j) == 2 && (i != 0 || j != 0)) {
        rome_roads[i-1][j-1] = rome_roads[j-1][i-1] = 1;
    }

    scanf("%lf %lf", &dock.x, &dock.y);
    scanf("%lf %lf", &home.x, &home.y);

    double min_cost = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rome_roads[i][j]) {
                double cost1 = dijkstra(N, i);
                double cost2 = dijkstra(j, N+1);
                double d1 = dist(dock, points[i]);
                double d2 = dist(points[j], home);
                double total_cost = cost1 + cost2 + rome_cost * d1 + rome_cost * d2;
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                }
            }
        }
    }

    printf("%.4lf\n", min_cost);
    return 0;
}