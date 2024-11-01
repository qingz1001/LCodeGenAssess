#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

typedef struct {
    int to;
    long long weight;
} Edge;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Adjacency list for the graph
    Edge *adj[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = NULL;
    }

    // Read edges and build adjacency list
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        Edge *new_edge = (Edge *)malloc(sizeof(Edge));
        new_edge->to = v - 1;
        new_edge->weight = w;
        new_edge->next = adj[u - 1];
        adj[u - 1] = new_edge;

        // Since the bus returns empty, we need to add the reverse edge with zero cost
        new_edge = (Edge *)malloc(sizeof(Edge));
        new_edge->to = u - 1;
        new_edge->weight = 0;
        new_edge->next = adj[v - 1];
        adj[v - 1] = new_edge;
    }

    // Bellman-Ford algorithm to find the shortest path from node 0 to all other nodes
    long long dist[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
    }
    dist[0] = 0;

    for (int k = 0; k < n - 1; ++k) {
        for (int i = 0; i < n; ++i) {
            Edge *current = adj[i];
            while (current != NULL) {
                if (dist[current->to] > dist[i] + current->weight) {
                    dist[current->to] = dist[i] + current->weight;
                }
                current = current->next;
            }
        }
    }

    // Sum up the distances to get the total minimum cost
    long long total_cost = 0;
    for (int i = 0; i < n; ++i) {
        total_cost += dist[i];
    }

    printf("%lld\n", total_cost);

    // Free allocated memory
    for (int i = 0; i < n; ++i) {
        Edge *current = adj[i];
        while (current != NULL) {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}