#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_M 100001

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
Edge* rev_graph[MAX_N];
int dist[MAX_N];
int rev_dist[MAX_N];
int n, m, x;

void add_edge(Edge** g, int from, int to, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = g[from];
    g[from] = e;
}

void dijkstra(Edge** g, int start, int* d) {
    int visited[MAX_N] = {0};
    for (int i = 1; i <= n; i++) {
        d[i] = INT_MAX;
    }
    d[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int min_dist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && d[j] < min_dist) {
                u = j;
                min_dist = d[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (Edge* e = g[u]; e; e = e->next) {
            int v = e->to;
            if (d[v] > d[u] + e->weight) {
                d[v] = d[u] + e->weight;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(graph, u, v, w);
        add_edge(rev_graph, v, u, w);
    }

    dijkstra(graph, x, dist);
    dijkstra(rev_graph, x, rev_dist);

    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (i != x) {
            int total_dist = dist[i] + rev_dist[i];
            if (total_dist > max_dist) {
                max_dist = total_dist;
            }
        }
    }

    printf("%d\n", max_dist);

    return 0;
}