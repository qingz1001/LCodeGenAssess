#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define INF INT_MAX

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    Edge edges[MAXN * (MAXN - 1) / 2];
    int size;
} Graph;

Graph graph[MAXN];
int dist[MAXN];
int parent[MAXN];

void add_edge(int u, int v, int w) {
    graph[u].edges[graph[u].size].to = v;
    graph[u].edges[graph[u].size].weight = w;
    graph[u].size++;
    graph[v].edges[graph[v].size].to = u;
    graph[v].edges[graph[v].size].weight = w;
    graph[v].size++;
}

void dijkstra(int start, int n) {
    int i, j, min, u, v, w;
    int visited[MAXN] = {0};

    for (i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (i = 1; i <= n; i++) {
        min = INF;
        for (j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        for (j = 0; j < graph[u].size; j++) {
            v = graph[u].edges[j].to;
            w = graph[u].edges[j].weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
}

int main() {
    int N, M, A, B, V, i, j, max_time = 0;
    scanf("%d %d", &N, &M);

    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &A, &B, &V);
        add_edge(A, B, V);
    }

    dijkstra(1, N);
    int shortest_path_time = dist[N];

    for (i = N; i != 1; i = parent[i]) {
        int u = i, v = parent[i];
        int original_weight = 0;
        for (j = 0; j < graph[u].size; j++) {
            if (graph[u].edges[j].to == v) {
                original_weight = graph[u].edges[j].weight;
                graph[u].edges[j].weight = INF;
                break;
            }
        }
        for (j = 0; j < graph[v].size; j++) {
            if (graph[v].edges[j].to == u) {
                graph[v].edges[j].weight = INF;
                break;
            }
        }

        dijkstra(1, N);
        if (dist[N] > max_time) {
            max_time = dist[N];
        }

        for (j = 0; j < graph[u].size; j++) {
            if (graph[u].edges[j].to == v) {
                graph[u].edges[j].weight = original_weight;
                break;
            }
        }
        for (j = 0; j < graph[v].size; j++) {
            if (graph[v].edges[j].to == u) {
                graph[v].edges[j].weight = original_weight;
                break;
            }
        }
    }

    printf("%d\n", max_time);
    return 0;
}