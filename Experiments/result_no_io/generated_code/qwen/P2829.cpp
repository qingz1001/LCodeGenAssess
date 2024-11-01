#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 5005
#define MAXM 100005
#define INF INT_MAX

typedef struct {
    int v, w;
} Edge;

int n, m, k;
Edge edges[MAXM];
int dist[MAXN][2];
int graph[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i][0] = dist[i][1] = INF;
    }
    dist[start][0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u][0] != INF && dist[v][0] > dist[u][0] + w) {
                dist[v][0] = dist[u][0] + w;
                dist[v][1] = dist[v][0];
            } else if (dist[u][0] != INF && dist[v][1] > dist[u][0] + w && dist[v][0] < dist[u][0] + w) {
                dist[v][1] = dist[u][0] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        graph[edges[i].u][edges[i].v] = graph[edges[i].v][edges[i].u] = edges[i].w;
    }

    dijkstra(1);

    if (dist[n][1] == INF) {
        printf("-1\n");
    } else {
        int count = 0;
        for (int i = 1; i <= n; ++i) {
            if (graph[i][n] < k) {
                count++;
            }
        }
        if (count > 0) {
            printf("%d\n", dist[n][1]);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}