#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

int min(int a, int b) {
    return a < b ? a : b;
}

void dijkstra(int n, int start, int *dist, Edge **graph, int *degree) {
    int *visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int i = 0; i < degree[u]; i++) {
            Edge e = graph[u][i];
            if (!visited[e.to]) {
                dist[e.to] = min(dist[e.to], dist[u] + e.weight);
            }
        }
    }

    free(visited);
}

int main() {
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);

    Edge **graph = (Edge **)malloc(n * sizeof(Edge *));
    int *degree = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        graph[i] = (Edge *)malloc(m * sizeof(Edge));
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u-1][degree[u-1]].to = v-1;
        graph[u-1][degree[u-1]].weight = w;
        degree[u-1]++;
    }

    int *dist_to_x = (int *)malloc(n * sizeof(int));
    dijkstra(n, x-1, dist_to_x, graph, degree);

    int max_path_length = 0;
    for (int i = 0; i < n; i++) {
        int round_trip = dist_to_x[i] + dist_to_x[i];
        if (round_trip > max_path_length) {
            max_path_length = round_trip;
        }
    }

    printf("%d\n", max_path_length);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(degree);
    free(dist_to_x);

    return 0;
}