#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9
#define MAXN 1001

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
} Edge;

Point points[MAXN];
Edge edges[MAXN * MAXN];
int edge_count = 0;
double dist[MAXN][MAXN];
double dissatisfaction_dirt, dissatisfaction_rome;
int n;

void add_edge(int u, int v, double weight) {
    edges[edge_count].u = u;
    edges[edge_count].v = v;
    dist[u][v] = weight;
    edge_count++;
}

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void read_input() {
    scanf("%lf %lf", &dissatisfaction_dirt, &dissatisfaction_rome);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    int u, v;
    while (1) {
        scanf("%d %d", &u, &v);
        if (u == 0 && v == 0) break;
        double distance = calculate_distance(points[u], points[v]);
        add_edge(u, v, distance * dissatisfaction_rome);
    }
    Point start, end;
    scanf("%lf %lf", &start.x, &start.y);
    scanf("%lf %lf", &end.x, &end.y);
    for (int i = 1; i <= n; i++) {
        double distance_start = calculate_distance(start, points[i]);
        double distance_end = calculate_distance(end, points[i]);
        add_edge(0, i, distance_start * dissatisfaction_dirt);
        add_edge(i, 0, distance_end * dissatisfaction_dirt);
    }
}

double min_cost[MAXN];
int visited[MAXN];

double dijkstra() {
    for (int i = 0; i <= n; i++) {
        min_cost[i] = INF;
        visited[i] = 0;
    }
    min_cost[0] = 0;

    for (int i = 0; i < n; i++) {
        int min_index = -1;
        double min_val = INF;
        for (int j = 0; j <= n; j++) {
            if (!visited[j] && min_cost[j] < min_val) {
                min_val = min_cost[j];
                min_index = j;
            }
        }
        if (min_index == -1) break;
        visited[min_index] = 1;

        for (int j = 0; j < edge_count; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            if (min_cost[u] + dist[u][v] < min_cost[v]) {
                min_cost[v] = min_cost[u] + dist[u][v];
            }
        }
    }
    return min_cost[n];
}

int main() {
    read_input();
    double result = dijkstra();
    printf("%.4lf\n", result);
    return 0;
}