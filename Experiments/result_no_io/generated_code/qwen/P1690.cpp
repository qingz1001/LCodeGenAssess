#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(int graph[MAX_N][MAX_N], int V, int src, int dist[]) {
    int visited[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int N, P;
    scanf("%d", &N);
    int graph[MAX_N][MAX_N] = {0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    scanf("%d", &P);
    int treasure[MAX_N] = {0};
    for (int i = 0; i < P; i++) {
        scanf("%d", &treasure[i]);
    }

    int total_distance = 0;
    int current_position = 0;

    for (int i = 0; i < P; i++) {
        int next_position = treasure[i] - 1;
        int dist[N];
        dijkstra(graph, N, current_position, dist);
        total_distance += dist[next_position];
        current_position = next_position;
    }

    int dist[N];
    dijkstra(graph, N, current_position, dist);
    total_distance += dist[N - 1];

    printf("%d\n", total_distance);

    return 0;
}