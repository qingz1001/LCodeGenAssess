#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define INF 1000000000

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(int n, int graph[MAX_N][MAX_N], int dist[]) {
    int visited[MAX_N];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int graph[MAX_N][MAX_N];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int dist[MAX_N];
    dijkstra(n, graph, dist);

    int total_cost = 0;
    for (int i = 1; i < n; i++) {
        total_cost += dist[i];
    }

    printf("%d\n", total_cost);

    return 0;
}