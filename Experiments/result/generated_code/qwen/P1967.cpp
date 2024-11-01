#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int dist[MAXN];

void add_edge(int from, int to, int weight) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    int visited[MAXN] = {0};
    while (1) {
        int min_dist = INF, u = -1;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to, w = e->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        dijkstra(x, n);
        printf("%d\n", dist[y]);
    }
    return 0;
}