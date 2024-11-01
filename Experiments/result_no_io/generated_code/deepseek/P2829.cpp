#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 5001
#define MAXM 100001
#define INF INT_MAX

typedef struct {
    int v, w;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN], next[MAXM], size;
} Graph;

Graph graph;
int dist[MAXN], dist2[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, int w) {
    graph.edges[graph.size].v = v;
    graph.edges[graph.size].w = w;
    graph.next[graph.size] = graph.head[u];
    graph.head[u] = graph.size++;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        dist2[i] = INF;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == INF) break;
        visited[u] = true;

        for (int j = graph.head[u]; j != -1; j = graph.next[j]) {
            int v = graph.edges[j].v;
            int w = graph.edges[j].w;
            if (dist[u] + w < dist[v]) {
                dist2[v] = dist[v];
                dist[v] = dist[u] + w;
            } else if (dist[u] + w < dist2[v] && dist[u] + w != dist[v]) {
                dist2[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        graph.head[i] = -1;
    }
    graph.size = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra(1, n);

    if (dist2[n] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist2[n]);
    }

    return 0;
}