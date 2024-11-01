#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 2000
#define MAX_E 2000000

typedef struct {
    int to;
    int weight;
} Edge;

int n, e;
Edge edges[MAX_E];
int dist[MAX_N];
int path_count[MAX_N];

void dijkstra(int start) {
    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        path_count[i] = 0;
    }
    dist[start] = 0;
    path_count[start] = 1;

    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (dist[j] != INT_MAX && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        for (int j = 0; j < e; ++j) {
            if (edges[j].to == u) {
                int v = edges[j].from;
                int w = edges[j].weight;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    path_count[v] = path_count[u];
                } else if (dist[v] == dist[u] + w) {
                    path_count[v] += path_count[u];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i < e; ++i) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    dijkstra(0);

    if (dist[n - 1] == INT_MAX) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[n - 1], path_count[n - 1]);
    }

    return 0;
}