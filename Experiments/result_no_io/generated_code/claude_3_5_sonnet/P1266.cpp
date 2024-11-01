#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 150
#define INF DBL_MAX

typedef struct {
    int to;
    int v;
    int l;
} Edge;

typedef struct {
    Edge* edges;
    int count;
    int capacity;
} AdjList;

AdjList graph[MAX_N];
double dist[MAX_N];
int prev[MAX_N];
int path[MAX_N];
int path_len;

void init_graph(int n) {
    for (int i = 0; i < n; i++) {
        graph[i].edges = NULL;
        graph[i].count = 0;
        graph[i].capacity = 0;
    }
}

void add_edge(int from, int to, int v, int l) {
    if (graph[from].count == graph[from].capacity) {
        graph[from].capacity = graph[from].capacity == 0 ? 1 : graph[from].capacity * 2;
        graph[from].edges = realloc(graph[from].edges, sizeof(Edge) * graph[from].capacity);
    }
    graph[from].edges[graph[from].count++] = (Edge){to, v, l};
}

void dijkstra(int n, int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    int visited[MAX_N] = {0};
    double speed = 70;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;
        visited[u] = 1;

        for (int j = 0; j < graph[u].count; j++) {
            Edge e = graph[u].edges[j];
            double new_speed = e.v == 0 ? speed : e.v;
            double time = (double)e.l / new_speed;
            if (dist[u] + time < dist[e.to]) {
                dist[e.to] = dist[u] + time;
                prev[e.to] = u;
            }
        }

        if (graph[u].count > 0) {
            Edge last_edge = graph[u].edges[graph[u].count - 1];
            speed = last_edge.v == 0 ? speed : last_edge.v;
        }
    }
}

void reconstruct_path(int start, int end) {
    path_len = 0;
    for (int v = end; v != -1; v = prev[v]) {
        path[path_len++] = v;
    }
    for (int i = 0; i < path_len / 2; i++) {
        int temp = path[i];
        path[i] = path[path_len - 1 - i];
        path[path_len - 1 - i] = temp;
    }
}

int main() {
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);

    init_graph(n);

    for (int i = 0; i < m; i++) {
        int a, b, v, l;
        scanf("%d %d %d %d", &a, &b, &v, &l);
        add_edge(a, b, v, l);
    }

    dijkstra(n, 0);
    reconstruct_path(0, d);

    for (int i = 0; i < path_len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(graph[i].edges);
    }

    return 0;
}