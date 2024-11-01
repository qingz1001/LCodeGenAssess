#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define INF 0x3f3f3f3f

int n, m, s, t;
int graph[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) dist[i] = -INF;
    dist[start] = 0;

    for (int k = 1; k <= n; k++) {
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (dist[i] != -INF && (u == -1 || dist[u] < dist[i])) u = i;

        for (int v = 1; v <= n; v++)
            if (graph[u][v] != -1)
                dist[v] = fmax(dist[v], fmin(dist[u], graph[u][v]));
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            graph[i][j] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = fmax(graph[u][v], w);
        graph[v][u] = fmax(graph[v][u], w);
    }

    dijkstra(s);

    printf("%d\n", dist[t]);

    return 0;
}