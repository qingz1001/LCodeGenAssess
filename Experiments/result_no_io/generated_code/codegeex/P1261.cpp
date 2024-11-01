#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 30000
#define MAXM 50000
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to;
    int weight;
};

struct Graph {
    int n;
    int m;
    struct Edge edges[MAXM];
    int head[MAXN];
    int degree[MAXN];
};

struct Dist {
    ll dist[MAXN];
    int visited[MAXN];
};

void add_edge(struct Graph *g, int u, int v, int w) {
    g->edges[g->m].to = v;
    g->edges[g->m].weight = w;
    g->head[u] = g->m++;
}

void dijkstra(struct Graph *g, int start, struct Dist *dist) {
    for (int i = 0; i < g->n; i++) {
        dist->dist[i] = INF;
        dist->visited[i] = 0;
    }
    dist->dist[start] = 0;
    dist->visited[start] = 1;
    for (int i = 0; i < g->n - 1; i++) {
        int min_dist = INF;
        int min_node = -1;
        for (int j = 0; j < g->n; j++) {
            if (!dist->visited[j] && dist->dist[j] < min_dist) {
                min_dist = dist->dist[j];
                min_node = j;
            }
        }
        if (min_node == -1) break;
        dist->visited[min_node] = 1;
        for (int j = g->head[min_node]; j < g->m; j++) {
            int to = g->edges[j].to;
            int weight = g->edges[j].weight;
            if (!dist->visited[to] && dist->dist[min_node] + weight < dist->dist[to]) {
                dist->dist[to] = dist->dist[min_node] + weight;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    struct Graph g = {n, 0};
    for (int i = 0; i < n; i++) {
        int rank;
        scanf("%d", &rank);
        g.degree[rank]++;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&g, u - 1, v - 1, w);
        add_edge(&g, v - 1, u - 1, w);
    }
    ll total_storage = 0;
    for (int i = 0; i < n; i++) {
        struct Dist dist = {0};
        dijkstra(&g, i, &dist);
        for (int j = 0; j < n; j++) {
            if (dist.dist[j] <= 1000) {
                total_storage += g.degree[j];
            }
        }
    }
    printf("%lld\n", total_storage);
    return 0;
}