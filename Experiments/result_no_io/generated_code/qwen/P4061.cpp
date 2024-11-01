#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define INF 0x3f3f3f3f

int n, m, S, T;
int dist[MAXN];
int graph[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    int visited[MAXN] = {0};
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;
        for (int v = 1; v <= n; ++v) {
            if (graph[u][v] != INF) {
                dist[v] = fmin(dist[v], dist[u] + graph[u][v]);
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = fmin(graph[u][v], w);
        graph[v][u] = fmin(graph[v][u], w);
    }

    dijkstra(S);

    int count = 0;
    for (int A = 1; A <= n; ++A) {
        if (dist[A] == INF) continue;
        dijkstra(A);
        if (dist[T] == INF) continue;
        for (int B = 1; B <= n; ++B) {
            if (B == A) continue;
            if (dist[B] == INF) continue;
            if (dist[S] == dist[A] + dist[B] + dist[T]) {
                ++count;
            }
        }
    }

    printf("%d\n", count / 2);

    return 0;
}