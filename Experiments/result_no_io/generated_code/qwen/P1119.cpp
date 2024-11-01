#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int v, w;
} Edge;

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

void dijkstra(int n, int s, int *dist, int **graph, int *times) {
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1, minDist = INF;
        for (int j = 0; j < n; j++) {
            if (times[j] == 0 && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        times[u]--;
        for (int j = 0; j < graph[u][0]; j++) {
            int v = graph[u][j + 1], w = graph[u][j + 2];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int times[n];
    for (int i = 0; i < n; i++) scanf("%d", &times[i]);
    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc((m + 2) * sizeof(int));
        graph[i][0] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][graph[u][0]++] = v;
        graph[u][graph[u][0]++] = w;
        graph[v][graph[v][0]++] = u;
        graph[v][graph[v][0]++] = w;
    }
    qsort(graph[0], m * 2, sizeof(int), cmp);

    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (times[x] > t || times[y] > t) {
            printf("-1\n");
        } else {
            int dist[n];
            dijkstra(n, x, dist, graph, times);
            if (dist[y] == INF) {
                printf("-1\n");
            } else {
                printf("%d\n", dist[y]);
            }
        }
    }

    for (int i = 0; i < n; i++) free(graph[i]);
    free(graph);
    return 0;
}