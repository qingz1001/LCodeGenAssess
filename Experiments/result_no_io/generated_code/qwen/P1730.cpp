#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 55
#define MAXM 1005
#define INF (INT_MAX / 2)

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXM];
int graph[MAXN][MAXN];
int dist[MAXN], prev[MAXN];

void dijkstra(int n, int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0) {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }
}

double getDensity(int n, int start, int end) {
    dijkstra(n, start);
    if (prev[end] == -1) return -1.0;

    double sum = 0.0;
    int count = 0;
    for (int u = end; u != start; u = prev[u]) {
        int v = prev[u];
        sum += graph[v][u];
        count++;
    }
    sum += graph[prev[end]][end];
    count++;

    return sum / count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        graph[a-1][b-1] = w;
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        double density = getDensity(n, x-1, y-1);
        if (density == -1.0) {
            printf("OMG!\n");
        } else {
            printf("%.3f\n", density);
        }
    }

    return 0;
}