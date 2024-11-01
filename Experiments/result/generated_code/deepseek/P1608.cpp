#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000
#define MAXE 4000000

typedef struct {
    int to, cost;
} Edge;

typedef struct {
    Edge edges[MAXE];
    int head[MAXN + 1];
    int next[MAXE];
    int edge_count;
} Graph;

void add_edge(Graph *graph, int from, int to, int cost) {
    int edge_index = graph->edge_count++;
    graph->edges[edge_index].to = to;
    graph->edges[edge_index].cost = cost;
    graph->next[edge_index] = graph->head[from];
    graph->head[from] = edge_index;
}

void dijkstra(Graph *graph, int start, int *dist, int *path_count, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        path_count[i] = 0;
    }
    dist[start] = 0;
    path_count[start] = 1;

    int visited[MAXN + 1] = {0};
    for (int i = 1; i <= n; i++) {
        int min_dist = INT_MAX, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int e = graph->head[u]; e != -1; e = graph->next[e]) {
            int v = graph->edges[e].to;
            int cost = graph->edges[e].cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                path_count[v] = path_count[u];
            } else if (dist[u] + cost == dist[v]) {
                path_count[v] += path_count[u];
            }
        }
    }
}

int main() {
    int n, e;
    scanf("%d %d", &n, &e);

    Graph graph = {0};
    for (int i = 1; i <= n; i++) {
        graph.head[i] = -1;
    }

    for (int i = 0; i < e; i++) {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        add_edge(&graph, from, to, cost);
    }

    int dist[MAXN + 1];
    int path_count[MAXN + 1];
    dijkstra(&graph, 1, dist, path_count, n);

    if (dist[n] == INT_MAX) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[n], path_count[n]);
    }

    return 0;
}