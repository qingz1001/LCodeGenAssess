#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1001
#define MAXM 100001

typedef struct {
    int v, w;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN];
    int cnt;
} Graph;

Graph graph;
int dist[MAXN];
int visited[MAXN];

void addEdge(int u, int v, int w) {
    graph.edges[graph.cnt].v = v;
    graph.edges[graph.cnt].w = w;
    graph.edges[graph.cnt].next = graph.head[u];
    graph.head[u] = graph.cnt++;
}

void dijkstra(int start) {
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
        visited[u] = 1;
        for (int j = graph.head[u]; j != -1; j = graph.edges[j].next) {
            int v = graph.edges[j].v;
            int w = graph.edges[j].w;
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
    graph.cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra(1);

    int totalTime = 0;
    for (int i = 2; i <= n; i++) {
        totalTime += dist[i];
    }

    for (int i = 2; i <= n; i++) {
        dijkstra(i);
        totalTime += dist[1];
    }

    printf("%d\n", totalTime);

    return 0;
}