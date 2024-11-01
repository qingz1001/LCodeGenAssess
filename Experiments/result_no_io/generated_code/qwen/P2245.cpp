#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

int n, m, q;
Edge edges[MAXN];
int graph[MAXN][MAXN];

void dijkstra(int start) {
    int dist[MAXN];
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    int visited[MAXN] = {0};
    for (int i = 0; i < n - 1; ++i) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        visited[u] = 1;
        for (int j = 1; j <= n; ++j) {
            if (graph[u][j] != INF && dist[j] > dist[u] + graph[u][j]) {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        graph[start][i] = graph[i][start] = dist[i];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        graph[a][b] = graph[b][a] = l;
    }
    scanf("%d", &q);
    for (int i = 0; i < n; ++i) {
        dijkstra(i + 1);
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (graph[a][b] == INF) {
            printf("impossible\n");
        } else {
            printf("%d\n", graph[a][b]);
        }
    }
    return 0;
}