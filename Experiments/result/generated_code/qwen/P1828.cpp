#include <stdio.h>
#include <stdlib.h>

#define MAX_PASTURES 800
#define MAX_ROUTES 1450
#define INF 999999

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(int graph[MAX_PASTURES][MAX_PASTURES], int n, int src, int dist[]) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

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
                dist[v] = min(dist[v], dist[u] + graph[u][v]);
            }
        }
    }
}

int main() {
    int N, P, C;
    scanf("%d %d %d", &N, &P, &C);

    int pasture[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &pasture[i]);
    }

    int graph[MAX_PASTURES][MAX_PASTURES] = {0};
    for (int i = 0; i < C; i++) {
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        graph[A-1][B-1] = D;
        graph[B-1][A-1] = D;
    }

    int total_distance = 0;
    for (int i = 0; i < N; i++) {
        int dist[MAX_PASTURES];
        dijkstra(graph, P, pasture[i]-1, dist);
        int min_dist = INF;
        for (int j = 0; j < P; j++) {
            min_dist = min(min_dist, dist[j]);
        }
        total_distance += min_dist;
    }

    printf("%d\n", total_distance);

    return 0;
}