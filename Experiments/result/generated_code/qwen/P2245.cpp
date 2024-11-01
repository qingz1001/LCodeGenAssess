#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int v, w;
} Edge;

int n, m, q;
Edge edges[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i)
        dist[i] = INF;
    dist[start] = 0;
    for (int i = 1; i <= n - 1; ++i) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        for (int j = 1; j <= m; ++j) {
            if (edges[j].v == u || edges[j].w == u) {
                int v = edges[j].v == u ? edges[j].w : edges[j].v;
                dist[v] = dist[u] > dist[v] ? dist[v] : dist[u];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &edges[i].v, &edges[i].w, &edges[i].w);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        dijkstra(a);
        if (dist[b] == INF)
            printf("impossible\n");
        else
            printf("%d\n", dist[b]);
    }
    return 0;
}