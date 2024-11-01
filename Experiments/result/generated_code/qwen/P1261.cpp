#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 30005
#define MAXM 150005

typedef struct {
    int to, weight;
} Edge;

int n, m;
int rank[MAXN];
Edge edges[MAXM];
int degree[MAXN];
int parent[MAXN], dist[MAXN];

void add_edge(int u, int v, int w) {
    edges[m].to = v;
    edges[m].weight = w;
    m++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    parent[start] = -1;
    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!degree[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        degree[u]--;
        for (int j = 0; j < m; j++) {
            if (edges[j].to == u) {
                int v = edges[j].to;
                int w = edges[j].weight;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &rank[i]);
    }
    for (int i = 1; i <= m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    long long total_storage = 0;
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        for (int j = 1; j <= n; j++) {
            if (degree[j]) continue;
            if (rank[j] >= rank[i] && dist[j] <= dist[i]) {
                degree[j]++;
            }
        }
        for (int j = 1; j <= n; j++) {
            if (degree[j]) continue;
            total_storage++;
        }
    }

    printf("%lld\n", total_storage);

    return 0;
}