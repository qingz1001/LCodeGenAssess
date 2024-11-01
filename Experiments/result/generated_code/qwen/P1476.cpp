#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 120

int n, m;
int graph[MAX_N + 1][MAX_N + 1];
int dist[MAX_N + 1];
int visited[MAX_N + 1];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != 0 && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }

    dijkstra(1);

    printf("%d\n", dist[n]);
    for (int i = 1; i <= n; i++) {
        if (dist[i] != INT_MAX) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}