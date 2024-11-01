#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2005
#define INF INT_MAX

typedef struct {
    int to, cost;
} Edge;

int n, e;
Edge edges[MAXN * MAXN];
int dist[MAXN], path_count[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        path_count[start][i] = 0;
    }
    dist[start] = 0;
    path_count[start][start] = 1;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        for (int j = 0; j < e; j++) {
            int v = edges[j].to;
            int c = edges[j].cost;
            if (u == edges[j].from) {
                if (dist[v] > dist[u] + c) {
                    dist[v] = dist[u] + c;
                    path_count[start][v] = path_count[start][u];
                } else if (dist[v] == dist[u] + c) {
                    path_count[start][v] += path_count[start][u];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i < e; i++) {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        edges[i] = (Edge){to, cost};
    }

    dijkstra(1);

    if (dist[n] == INF) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[n], path_count[1][n]);
    }

    return 0;
}