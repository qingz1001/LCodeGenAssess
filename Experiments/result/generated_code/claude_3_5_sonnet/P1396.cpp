#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_M 20005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int vis[MAX_N];
int n, m, s, t;

void addEdge(int u, int v, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

int dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (Edge* e = graph[u]; e; e = e->next) {
            int v = e->to;
            int max_dist = (dist[u] > e->weight) ? dist[u] : e->weight;
            if (max_dist < dist[v]) {
                dist[v] = max_dist;
            }
        }
    }

    return dist[t];
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    printf("%d\n", dijkstra());

    return 0;
}