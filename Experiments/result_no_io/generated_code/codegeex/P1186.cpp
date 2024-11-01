#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1001

int dist[MAXN];
int graph[MAXN][MAXN];
int n, m;

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    int visited[MAXN] = {0};
    visited[start] = 1;

    for (int i = 1; i < n; i++) {
        int min_dist = INT_MAX;
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] != -1 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b, v;
        scanf("%d %d %d", &a, &b, &v);
        graph[a][b] = v;
        graph[b][a] = v;
    }

    dijkstra(1);

    int max_time = dist[n];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] != -1) {
                graph[i][j] = 0;
                dijkstra(1);
                if (dist[n] > max_time) {
                    max_time = dist[n];
                }
                graph[i][j] = v;
            }
        }
    }

    printf("%d\n", max_time);
    return 0;
}