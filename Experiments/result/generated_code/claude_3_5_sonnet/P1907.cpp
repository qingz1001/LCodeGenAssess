#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 1000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int to;
    double weight;
} Edge;

Point points[MAX_N + 2];
Edge* graph[MAX_N + 2];
int graph_size[MAX_N + 2];
double dist[MAX_N + 2];
int visited[MAX_N + 2];

double dirt_cost, rome_cost;
int N;

double euclidean_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void add_edge(int from, int to, double weight) {
    graph[from] = realloc(graph[from], (graph_size[from] + 1) * sizeof(Edge));
    graph[from][graph_size[from]++] = (Edge){to, weight};
}

void dijkstra(int start) {
    for (int i = 0; i <= N + 1; i++) {
        dist[i] = DBL_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 0; i <= N + 1; i++) {
        int u = -1;
        double min_dist = DBL_MAX;
        for (int j = 0; j <= N + 1; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int j = 0; j < graph_size[u]; j++) {
            int v = graph[u][j].to;
            double weight = graph[u][j].weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
}

int main() {
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    int i, j;
    while (scanf("%d %d", &i, &j) && (i != 0 || j != 0)) {
        double distance = euclidean_distance(points[i], points[j]);
        add_edge(i, j, distance * rome_cost);
        add_edge(j, i, distance * rome_cost);
    }

    scanf("%lf %lf", &points[0].x, &points[0].y);  // Dock
    scanf("%lf %lf", &points[N+1].x, &points[N+1].y);  // Your home

    for (i = 0; i <= N + 1; i++) {
        for (j = i + 1; j <= N + 1; j++) {
            if (i == j) continue;
            double distance = euclidean_distance(points[i], points[j]);
            add_edge(i, j, distance * dirt_cost);
            add_edge(j, i, distance * dirt_cost);
        }
    }

    dijkstra(0);

    printf("%.4f\n", dist[N+1]);

    for (i = 0; i <= N + 1; i++) {
        free(graph[i]);
    }

    return 0;
}