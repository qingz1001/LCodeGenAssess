#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 50005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int node;
    long long dist;
} Node;

typedef struct {
    Edge edges[MAXM * 2];
    int head[MAXN];
    int cnt;
} Graph;

Graph graph;
long long distS[MAXN], distT[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, int w) {
    graph.edges[graph.cnt].to = v;
    graph.edges[graph.cnt].weight = w;
    graph.edges[graph.cnt].next = graph.head[u];
    graph.head[u] = graph.cnt++;

    graph.edges[graph.cnt].to = u;
    graph.edges[graph.cnt].weight = w;
    graph.edges[graph.cnt].next = graph.head[v];
    graph.head[v] = graph.cnt++;
}

void dijkstra(int start, long long dist[]) {
    for (int i = 0; i < MAXN; i++) {
        dist[i] = LLONG_MAX;
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
        visited[u] = true;
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
    int n, m, S, T;
    scanf("%d %d %d %d", &n, &m, &S, &T);

    for (int i = 0; i < MAXN; i++) {
        graph.head[i] = -1;
    }
    graph.cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra(S, distS);
    dijkstra(T, distT);

    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (distS[i] + distT[j] == distS[T] && distS[j] + distT[i] == distS[T]) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}