#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int to;
    int weight;
} Edge;

int n, m, x;
Edge edges[100005];
int dist[1005];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = edges[j].to;
            int v = edges[j].weight;
            if (dist[u] != INF && dist[v] > dist[u] + edges[j].weight) {
                dist[v] = dist[u] + edges[j].weight;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].to, &edges[i].weight);
    }

    // Run Dijkstra from the party farm
    dijkstra(x);

    // Find the maximum round trip distance
    int max_distance = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] != INF) {
            max_distance = fmax(max_distance, dist[i] * 2);
        }
    }

    printf("%d\n", max_distance);

    return 0;
}