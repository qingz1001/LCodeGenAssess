#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define INF 0x3f3f3f3f

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXN];
int degree[MAXN];
int dist[MAXN];

void dijkstra(int n, int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        for (int j = 1; j <= degree[u]; ++j) {
            int v = edges[u * 2 + j].to;
            int w = edges[u * 2 + j].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i * 2 - 1] = (Edge){v, w};
        edges[i * 2] = (Edge){u, w};
        degree[u]++;
        degree[v]++;
    }
    dijkstra(n, 1);
    printf("%d\n", dist[n]);
    return 0;
}