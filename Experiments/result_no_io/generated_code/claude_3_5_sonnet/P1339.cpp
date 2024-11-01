#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 2501
#define MAX_M 6201

typedef struct {
    int v, w;
} Edge;

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} AdjList;

AdjList graph[MAX_N];
int dist[MAX_N];
bool visited[MAX_N];

void init_graph(int n) {
    for (int i = 1; i <= n; i++) {
        graph[i].edges = NULL;
        graph[i].size = 0;
        graph[i].capacity = 0;
    }
}

void add_edge(int u, int v, int w) {
    if (graph[u].size == graph[u].capacity) {
        graph[u].capacity = graph[u].capacity == 0 ? 1 : graph[u].capacity * 2;
        graph[u].edges = realloc(graph[u].edges, sizeof(Edge) * graph[u].capacity);
    }
    graph[u].edges[graph[u].size++] = (Edge){v, w};
}

int dijkstra(int n, int s, int t) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1 || u == t) break;
        visited[u] = true;

        for (int j = 0; j < graph[u].size; j++) {
            Edge e = graph[u].edges[j];
            if (dist[u] + e.w < dist[e.v]) {
                dist[e.v] = dist[u] + e.w;
            }
        }
    }

    return dist[t];
}

int main() {
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);

    init_graph(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int result = dijkstra(n, s, t);
    printf("%d\n", result);

    for (int i = 1; i <= n; i++) {
        free(graph[i].edges);
    }

    return 0;
}