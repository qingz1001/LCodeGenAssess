#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_M 100005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], dist[MAX_N], vis[MAX_N];
int n, m, q, edge_cnt;

void init() {
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
}

void add_edge(int u, int v, int w) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].weight = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dijkstra(int s) {
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

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            if (dist[v] > (dist[u] > w ? dist[u] : w)) {
                dist[v] = (dist[u] > w ? dist[u] : w);
            }
        }
    }
}

void remove_edge(int u, int v) {
    for (int e = head[u]; e != -1; e = edges[e].next) {
        if (edges[e].to == v) {
            edges[e].weight = INF;
            break;
        }
    }
    for (int e = head[v]; e != -1; e = edges[e].next) {
        if (edges[e].to == u) {
            edges[e].weight = INF;
            break;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    init();

    for (int i = 0; i < m; i++) {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        add_edge(u, v, t);
        add_edge(v, u, t);
    }

    for (int i = 0; i < q; i++) {
        int k, u, v;
        scanf("%d%d%d", &k, &u, &v);
        if (k == 1) {
            dijkstra(u);
            printf("%d\n", dist[v]);
        } else {
            remove_edge(u, v);
        }
    }

    return 0;
}