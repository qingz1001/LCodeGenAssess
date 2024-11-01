#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 5005
#define MAXM 100005

typedef struct {
    int to, weight;
} Edge;

int n, m, k;
Edge edges[MAXM];
int dist[MAXN], dist2[MAXN];
int adj[MAXN][MAXN];
int degree[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        dist2[i] = INT_MAX;
    }
    dist[start] = 0;
    dist2[start] = 0;

    int visited[MAXN] = {0};
    int count = 0;
    while (count < n) {
        int u = -1, min_dist = INT_MAX;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                u = i;
                min_dist = dist[i];
            }
        }

        visited[u] = 1;
        count++;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != 0) {
                int new_dist = dist[u] + adj[u][v];
                if (new_dist < dist[v]) {
                    dist2[v] = dist[v];
                    dist[v] = new_dist;
                } else if (new_dist > dist[v] && new_dist < dist2[v]) {
                    dist2[v] = new_dist;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;
        degree[u]++;
        degree[v]++;
    }

    dijkstra(1);

    if (dist[n] == INT_MAX || dist2[n] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dist2[n]);
    }

    return 0;
}