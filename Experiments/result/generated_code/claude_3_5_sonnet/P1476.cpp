#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 120
#define INF 1000000000

int n, m;
int graph[MAX_N+1][MAX_N+1];
int dist[MAX_N+1];
int visited[MAX_N+1];
int path[MAX_N+1];

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }
}

void print_path(int node) {
    if (node != 1) {
        print_path(path[node]);
    }
    printf("%d ", node);
}

int main() {
    scanf("%d", &n);
    scanf("%d", &m);

    memset(graph, 0, sizeof(graph));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (graph[u][v] == 0 || w < graph[u][v]) {
            graph[u][v] = w;
        }
    }

    dijkstra();

    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_dist && dist[i] != INF) {
            max_dist = dist[i];
        }
    }

    printf("%d\n", max_dist);
    print_path(n);
    printf("\n");

    return 0;
}