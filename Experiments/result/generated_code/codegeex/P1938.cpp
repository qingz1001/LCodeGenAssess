#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 220
#define MAX_EDGES 600

int d, p, c, f, s;
int graph[MAX_CITIES][MAX_CITIES]; // Adjacency matrix for the graph
int dist[MAX_CITIES]; // Distance array for Bellman-Ford algorithm

void bellman_ford(int start) {
    memset(dist, 0, sizeof(dist));
    dist[start] = d;

    for (int i = 1; i < c; i++) {
        for (int u = 1; u <= c; u++) {
            for (int v = 1; v <= c; v++) {
                if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] > dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &d, &p, &c, &f, &s);

    // Initialize the graph with 0s
    memset(graph, 0, sizeof(graph));

    // Read the paths
    for (int i = 0; i < p; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = d;
    }

    // Read the jet routes
    for (int i = 0; i < f; i++) {
        int j, k, t;
        scanf("%d %d %d", &j, &k, &t);
        if (dist[j] != INT_MAX && dist[j] + t > dist[k]) {
            dist[k] = dist[j] + t;
        }
    }

    bellman_ford(s);

    int max_profit = 0;
    for (int i = 1; i <= c; i++) {
        if (dist[i] == INT_MAX) {
            printf("-1\n");
            return 0;
        }
        max_profit = max_profit > dist[i] ? max_profit : dist[i];
    }

    printf("%d\n", max_profit);
    return 0;
}