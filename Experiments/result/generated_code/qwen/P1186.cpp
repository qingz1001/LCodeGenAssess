#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 1000
#define INF 1000000

typedef struct {
    int city;
    int time;
} Edge;

int compare(const void *a, const void *b) {
    return ((Edge *)a)->time - ((Edge *)b)->time;
}

void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int n, int start, int dist[]) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    int visited[MAX_CITIES] = {0};
    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[MAX_CITIES][MAX_CITIES] = {0};

    for (int i = 0; i < m; i++) {
        int a, b, v;
        scanf("%d %d %d", &a, &b, &v);
        graph[a-1][b-1] = v;
        graph[b-1][a-1] = v;
    }

    int dist[MAX_CITIES];
    dijkstra(graph, n, 0, dist);

    int max_time = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > max_time) {
            max_time = dist[i];
        }
    }

    printf("%d\n", max_time);

    return 0;
}