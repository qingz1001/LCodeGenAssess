#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000
#define INF INT_MAX

typedef struct {
    int to, cost;
} Edge;

typedef struct {
    Edge edges[MAXN];
    int size;
} AdjList;

AdjList graph[MAXN];
int dist[MAXN];
long long count[MAXN];

void add_edge(int from, int to, int cost) {
    graph[from].edges[graph[from].size].to = to;
    graph[from].edges[graph[from].size].cost = cost;
    graph[from].size++;
}

void dijkstra(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        count[i] = 0;
    }
    dist[1] = 0;
    count[1] = 1;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;

        for (int j = 0; j < graph[u].size; j++) {
            int v = graph[u].edges[j].to;
            int cost = graph[u].edges[j].cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                count[v] = count[u];
            } else if (dist[u] + cost == dist[v]) {
                count[v] += count[u];
            }
        }
    }
}

int main() {
    int n, e;
    scanf("%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        add_edge(from, to, cost);
    }

    dijkstra(n);

    if (dist[n] == INF) {
        printf("No answer\n");
    } else {
        printf("%d %lld\n", dist[n], count[n]);
    }

    return 0;
}