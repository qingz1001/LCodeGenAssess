#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000
#define INF 1000000000

int n, e;
int dist[MAXN + 1], path_count[MAXN + 1], visited[MAXN + 1];
int graph[MAXN + 1][MAXN + 1];

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        path_count[i] = 0;
        visited[i] = 0;
    }
    dist[1] = 0;
    path_count[1] = 1;

    for (int i = 1; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path_count[v] = path_count[u];
            } else if (graph[u][v] && dist[u] + graph[u][v] == dist[v]) {
                path_count[v] += path_count[u];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        graph[u][v] = c;
    }

    dijkstra();

    if (path_count[n] == 0) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[n], path_count[n]);
    }

    return 0;
}