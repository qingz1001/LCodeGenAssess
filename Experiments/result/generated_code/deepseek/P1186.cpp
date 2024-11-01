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
int visited[MAXN];

void add_edge(int u, int v, int w) {
    graph[u].edges[graph[u].size].to = v;
    graph[u].edges[graph[u].size].weight = w;
    graph[u].size++;
    graph[v].edges[graph[v].size].to = u;
    graph[v].edges[graph[v].size].weight = w;
    graph[v].size++;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;
        for (int j = 0; j < graph[u].size; j++) {
            int v = graph[u].edges[j].to;
            int w = graph[u].edges[j].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, v;
        scanf("%d %d %d", &a, &b, &v);
        add_edge(a, b, v);
    }

    dijkstra(1, n);
    int original_shortest_path = dist[n];
    int max_time = 0;

    for (int u = 1; u <= n; u++) {
        for (int j = 0; j < graph[u].size; j++) {
            int v = graph[u].edges[j].to;
            int w = graph[u].edges[j].weight;
            if (dist[u] + w == dist[v]) {
                int temp = graph[u].edges[j].weight;
                graph[u].edges[j].weight = INF;
                graph[v].edges[j].weight = INF;
                dijkstra(1, n);
                if (dist[n] != INF) {
                    max_time = (dist[n] > max_time) ? dist[n] : max_time;
                }
                graph[u].edges[j].weight = temp;
                graph[v].edges[j].weight = temp;
            }
        }
    }

    printf("%d\n", max_time);
    return 0;
}