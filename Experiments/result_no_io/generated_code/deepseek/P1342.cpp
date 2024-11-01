#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005
#define MAXM 1000005

typedef struct {
    int to, weight, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
long long dist[MAXN];
int visited[MAXN];

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = LLONG_MAX;
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

        if (dist[u] == LLONG_MAX) break;
        visited[u] = 1;

        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            int w = edges[j].weight;
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
        head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w); // Since the bus returns to the starting point
    }

    dijkstra(1, n);

    long long total_cost = 0;
    for (int i = 2; i <= n; i++) {
        total_cost += dist[i];
    }

    printf("%lld\n", total_cost * 2); // Double the cost since they need to return

    return 0;
}