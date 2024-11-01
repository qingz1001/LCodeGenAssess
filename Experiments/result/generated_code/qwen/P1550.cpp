#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 305
#define INF 0x3f3f3f3f

int n;
int W[MAXN];
int P[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    int visited[MAXN] = {0};
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = 1;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && P[u][v] != 0) {
                dist[v] = dist[v] > dist[u] + P[u][v] ? dist[u] + P[u][v] : dist[v];
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &W[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &P[i][j]);
        }
    }

    int min_cost = INF;
    for (int i = 0; i < n; ++i) {
        dijkstra(i);
        int cost = 0;
        for (int j = 0; j < n; ++j) {
            cost += dist[j] == INF ? W[j] : dist[j];
        }
        min_cost = min_cost > cost ? cost : min_cost;
    }

    printf("%d\n", min_cost);

    return 0;
}