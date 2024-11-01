#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int v, w;
} Edge;

typedef struct {
    int to, weight;
} GraphEdge;

typedef struct {
    GraphEdge *edges;
    int size;
} Graph;

void addEdge(Graph *graph, int from, int to, int weight) {
    graph->edges[from].to = to;
    graph->edges[from].weight = weight;
    graph->size++;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(Graph *graph, int start, int *dist, int n) {
    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (graph->edges[j].to != -1 && dist[j] != INF && dist[j] + graph->edges[j].weight < dist[graph->edges[j].to]) {
                dist[graph->edges[j].to] = dist[j] + graph->edges[j].weight;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph graph;
    graph.edges = (GraphEdge *)malloc(n * sizeof(GraphEdge));
    for (int i = 0; i < n; i++) {
        graph.edges[i].to = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(&graph, u - 1, v - 1, w);
        addEdge(&graph, v - 1, u - 1, 0); // Local connection has zero time
    }

    int *dist = (int *)malloc((n + 1) * sizeof(int));
    dijkstra(&graph, 0, dist, n);

    printf("%d\n", dist[n - 1]);

    free(graph.edges);
    free(dist);

    return 0;
}