#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define MAXP 40005
#define INF 0x3f3f3f3f

int n, p, t;
int adj[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    int visited[MAXN] = {0};
    for (int i = 0; i < n - 1; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        visited[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != INF && !visited[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &p, &t);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = (i == j ? 0 : INF);
        }
    }
    for (int i = 0; i < p; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        adj[a][b] = adj[b][a] = l;
    }
    dijkstra(1);
    int max_path = 0;
    for (int i = 1; i <= n; i++) {
        max_path = (max_path > dist[i] ? max_path : dist[i]);
    }
    printf("%d\n", max_path);
    return 0;
}