#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000
#define INF INT_MAX

int n, e;
int dist[MAXN + 1], path_count[MAXN + 1];
int adj[MAXN + 1][MAXN + 1];

void dijkstra() {
    bool visited[MAXN + 1] = {false};
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        path_count[i] = 0;
    }
    dist[1] = 0;
    path_count[1] = 1;

    for (int i = 1; i < n; i++) {
        int min_dist = INF;
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    path_count[v] = path_count[u];
                } else if (dist[u] + adj[u][v] == dist[v]) {
                    path_count[v] += path_count[u];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        adj[u][v] = c;
    }

    dijkstra();

    if (dist[n] == INF) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[n], path_count[n]);
    }

    return 0;
}