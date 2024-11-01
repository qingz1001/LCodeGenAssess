#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1001
#define MAXM 100001

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], dist[MAXN], dist_back[MAXN];
int n, m, x, edge_count;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dijkstra(int start, int *dist) {
    int visited[MAXN] = {0};
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].v, w = edges[j].w;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 1; i <= n; i++) head[i] = -1;
    edge_count = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    dijkstra(x, dist_back);

    for (int i = 1; i <= n; i++) {
        if (i != x) {
            dijkstra(i, dist);
            dist_back[i] += dist[x];
        }
    }

    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist_back[i] > max_dist) {
            max_dist = dist_back[i];
        }
    }

    printf("%d\n", max_dist);
    return 0;
}