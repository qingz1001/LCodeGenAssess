#include <stdio.h>
#include <stdlib.h>

#define MAXN 25
#define INF 0x3f3f3f3f

int n, m, k, e;
int graph[MAXN][MAXN];
int unavailable[MAXN][2];

void dijkstra(int start, int dist[]) {
    for (int i = 1; i <= m; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 1; i <= m; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= m; j++) {
            if (!unavailable[j][0] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        unavailable[u][0] = 1;
        for (int v = 1; v <= m; v++) {
            if (graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &e);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 0; i < e; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        graph[a][b] = graph[b][a] = c;
    }
    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        unavailable[p][0] = 1;
        unavailable[p][1] = b;
    }

    int total_cost = 0;
    int current_day = 1;
    while (current_day <= n) {
        int dist[MAXN];
        dijkstra(1, dist);
        total_cost += dist[m];
        for (int i = 1; i <= m; i++) {
            if (dist[i] == INF) {
                unavailable[i][0] = 1;
                unavailable[i][1] = current_day;
            } else {
                unavailable[i][0] = 0;
            }
        }
        current_day++;
    }

    printf("%d\n", total_cost + k * (n - 1));
    return 0;
}