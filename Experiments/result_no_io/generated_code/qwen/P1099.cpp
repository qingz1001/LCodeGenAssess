#include <stdio.h>
#include <stdlib.h>

#define MAXN 305
#define INF 0x3f3f3f3f

int n, s;
int graph[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) dist[i] = INF;
    dist[start] = 0;

    int visited[MAXN] = {0};
    for (int i = 1; i <= n; ++i) {
        int min_dist = INF, min_node = -1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_node = j;
            }
        }

        visited[min_node] = 1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && graph[min_node][j] != INF) {
                dist[j] = fmin(dist[j], dist[min_node] + graph[min_node][j]);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }

    for (int i = 1; i <= n - 1; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int center = 1;
    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
        int max_dist = 0;
        for (int j = 1; j <= n; ++j) {
            max_dist = fmax(max_dist, dist[j]);
        }
        if (max_dist > dist[center]) center = i;
    }

    dijkstra(center);

    int ecc = 0;
    for (int i = 1; i <= n; ++i) {
        ecc = fmax(ecc, dist[i]);
    }

    printf("%d\n", ecc);

    return 0;
}