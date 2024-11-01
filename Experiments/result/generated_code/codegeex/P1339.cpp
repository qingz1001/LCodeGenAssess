#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2500
#define MAXM 6200
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int dist[MAXN + 1];
int visited[MAXN + 1];
Edge edges[MAXM + 1];
int graph[MAXN + 1][MAXN + 1];

void addEdge(int u, int v, int w) {
    graph[u][v] = w;
}

void dijkstra(int n, int s, int t) {
    memset(dist, INF, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        int minDist = INF, minNode = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minNode = j;
            }
        }
        if (minNode == -1) break;
        visited[minNode] = 1;

        for (int j = 1; j <= n; j++) {
            if (!visited[j] && graph[minNode][j] != 0 && dist[minNode] != INF && dist[minNode] + graph[minNode][j] < dist[j]) {
                dist[j] = dist[minNode] + graph[minNode][j];
            }
        }
    }
}

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra(n, s, t);

    printf("%d\n", dist[t]);
    return 0;
}