#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_M 5 * MAX_N

typedef struct {
    int v;
    int w;
    int t;
} Edge;

int n, m;
Edge edges[MAX_M];
int rank[MAX_N];
int graph[MAX_N][MAX_N];
int visited[MAX_N];

void dijkstra(int start, int dist[]) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    visited[start] = 1;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0) {
                dist[v] = (dist[v] > dist[u] + graph[u][v]) ? dist[u] + graph[u][v] : dist[v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &rank[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].t);
        edges[i].a--;
        edges[i].b--;
        graph[edges[i].a][edges[i].b] = edges[i].t;
        graph[edges[i].b][edges[i].a] = edges[i].t;
    }

    int total_storage = 0;

    for (int i = 0; i < n; i++) {
        int dist[n];
        dijkstra(i, dist);

        int count = 0;
        for (int j = 0; j < n; j++) {
            if (rank[j] >= rank[i] && dist[j] <= dist[i]) {
                count++;
            }
        }
        total_storage += count;
    }

    printf("%d\n", total_storage);

    return 0;
}