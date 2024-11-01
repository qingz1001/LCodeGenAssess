#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2505
#define MAXM 6205

typedef struct {
    int v, w;
} Edge;

int n, m, s, t;
Edge edges[MAXM];
int dist[MAXN];

void dijkstra() {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;

    while (1) {
        int u = -1, min_dist = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] < min_dist && !visited[i]) {
                min_dist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int i = 0; i < m; ++i) {
            if (edges[i].v == u) {
                int v = edges[i].u;
                if (!visited[v] && dist[u] + edges[i].w < dist[v]) {
                    dist[v] = dist[u] + edges[i].w;
                }
            } else if (edges[i].u == u) {
                int v = edges[i].v;
                if (!visited[v] && dist[u] + edges[i].w < dist[v]) {
                    dist[v] = dist[u] + edges[i].w;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    dijkstra();

    printf("%d\n", dist[t]);

    return 0;
}