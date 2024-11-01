#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define INF 0x3f3f3f3f

int n, m, q;
int graph[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    int visited[MAXN] = {0};
    for (int i = 1; i <= n; ++i) {
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
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        graph[x][y] = fmin(graph[x][y], z);
        graph[y][x] = fmin(graph[y][x], z);
    }

    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);

        dijkstra(x);
        if (dist[y] == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", dist[y]);
        }
    }

    return 0;
}