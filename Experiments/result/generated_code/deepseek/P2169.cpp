#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define MAXM 1000005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN];
    int size;
} Graph;

Graph graph;
int dist[MAXN];
int visited[MAXN];

void add_edge(int u, int v, int w) {
    graph.edges[graph.size].to = v;
    graph.edges[graph.size].weight = w;
    graph.edges[graph.size].next = graph.head[u];
    graph.head[u] = graph.size++;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
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

        if (dist[u] == INT_MAX) break;
        visited[u] = 1;

        for (int j = graph.head[u]; j != -1; j = graph.edges[j].next) {
            int v = graph.edges[j].to;
            int w = graph.edges[j].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        graph.head[i] = -1;
    }
    graph.size = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    dijkstra(1, n);

    printf("%d\n", dist[n]);

    return 0;
}