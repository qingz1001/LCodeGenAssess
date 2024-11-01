#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define INF 1e9

typedef struct {
    int to, cost;
} Edge;

Edge edges[MAXN * MAXN];
int adj[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int n, int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n; j++) {
            if (adj[j][start] != INF && dist[j] > dist[start] + adj[j][start]) {
                dist[j] = dist[start] + adj[j][start];
            }
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= m; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        adj[u][v] = adj[v][u] = t;
    }

    while (q--) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        if (k == 1) {
            dijkstra(n, u);
            printf("%d\n", dist[v]);
        } else if (k == 2) {
            adj[u][v] = adj[v][u] = INF;
        }
    }

    return 0;
}