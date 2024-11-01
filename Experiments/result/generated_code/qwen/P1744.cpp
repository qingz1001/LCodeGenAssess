#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 105
#define INF 1e9

int n, m;
double dist[MAXN];
int visited[MAXN];
int graph[MAXN][MAXN];

void dijkstra(int start) {
    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 0; v <= n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 0; v <= n; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                dist[v] = fmin(dist[v], dist[u] + graph[u][v]);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    double x, y;
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &x, &y);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        double dx = x[u] - x[v];
        double dy = y[u] - y[v];
        graph[u][v] = sqrt(dx * dx + dy * dy);
        graph[v][u] = graph[u][v];
    }

    int s, t;
    scanf("%d %d", &s, &t);

    dijkstra(s);

    printf("%.2f\n", dist[t]);

    return 0;
}