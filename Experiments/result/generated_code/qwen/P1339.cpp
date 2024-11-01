#include <stdio.h>
#include <stdlib.h>

#define MAXN 2505
#define INF 0x3f3f3f3f

typedef struct {
    int to, weight;
} Edge;

int dist[MAXN];
Edge edges[6205];
int edge_count[MAXN];

void dijkstra(int n, int s, int t) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[s] = 0;
    int visited[MAXN] = {0};
    while (1) {
        int min_dist = INF, u = -1;
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1 || u == t) break;
        visited[u] = 1;
        for (int i = 0; i < edge_count[u]; ++i) {
            int v = edges[edge_count[u] * 2 + i].to;
            int w = edges[edge_count[u] * 2 + i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i * 2] = (Edge){v, w};
        edges[i * 2 + 1] = (Edge){u, w};
        edge_count[u]++;
        edge_count[v]++;
    }
    dijkstra(n, s, t);
    printf("%d\n", dist[t]);
    return 0;
}