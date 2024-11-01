#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

typedef struct {
    int to, weight;
} Edge;

int n, m;
Edge edges[500000];
int dist[1001];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    int *visited = (int *)calloc(n + 1, sizeof(int));
    while (1) {
        int u = -1;
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && (u == -1 || dist[u] > dist[v])) {
                u = v;
            }
        }
        if (u == -1) break;

        visited[u] = 1;
        for (int i = 0; i < m; ++i) {
            if (edges[i].to == u) {
                int v = edges[i].from;
                int weight = edges[i].weight;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                }
            } else if (edges[i].from == u) {
                int v = edges[i].to;
                int weight = edges[i].weight;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    free(visited);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, v;
        scanf("%d %d %d", &a, &b, &v);
        edges[i].from = a;
        edges[i].to = b;
        edges[i].weight = v;
    }

    dijkstra(1);

    printf("%d\n", dist[n]);

    return 0;
}