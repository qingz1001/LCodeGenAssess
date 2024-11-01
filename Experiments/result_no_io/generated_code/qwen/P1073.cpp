#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int n, m;
int price[MAXN];
int graph[MAXN][MAXN];

void dijkstra(int start, int dist[]) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        for (int v = 1; v <= n; ++v) {
            if (graph[u][v] != INF) {
                dist[v] = dist[v] > dist[u] + graph[u][v] ? dist[u] + graph[u][v] : dist[v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &price[i]);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        graph[x][y] = z == 1 ? graph[x][y] : (graph[x][y] > 0 ? graph[x][y] : graph[y][x]);
        if (z == 2) {
            graph[y][x] = graph[x][y];
        }
    }

    int max_profit = 0;
    int dist_to_n[n + 1];
    dijkstra(n, dist_to_n);

    for (int i = 1; i <= n; ++i) {
        if (dist_to_n[i] != INF) {
            int profit = price[i] - dist_to_n[i];
            if (profit > max_profit) {
                max_profit = profit;
            }
        }
    }

    printf("%d\n", max_profit);

    return 0;
}