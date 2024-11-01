#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 200
#define MAX_M 19900 // N*(N-1)/2
#define INF INT_MAX

int N, M, Q;
int rebuild_time[MAX_N];
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

void init_graph() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void dijkstra(int start, int time) {
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < N; i++) {
        int min_dist = INF, u = -1;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && rebuild_time[j] <= time && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && rebuild_time[v] <= time && graph[u][v] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &rebuild_time[i]);
    }

    init_graph();

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);

        if (rebuild_time[x] > t || rebuild_time[y] > t) {
            printf("-1\n");
            continue;
        }

        dijkstra(x, t);

        if (dist[y] == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", dist[y]);
        }
    }

    return 0;
}