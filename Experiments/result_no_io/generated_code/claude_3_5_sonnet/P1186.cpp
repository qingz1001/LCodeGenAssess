#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_M 500500

int N, M;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;

    for (int i = 1; i <= N; i++) {
        int u = -1;
        int min_dist = INT_MAX;
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (graph[u][v] && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    memset(graph, 0, sizeof(graph));

    for (int i = 0; i < M; i++) {
        int A, B, V;
        scanf("%d %d %d", &A, &B, &V);
        graph[A][B] = graph[B][A] = V;
    }

    dijkstra(N);
    int shortest = dist[1];

    int max_time = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (graph[i][j]) {
                int original = graph[i][j];
                graph[i][j] = graph[j][i] = 0;
                dijkstra(N);
                if (dist[1] > max_time) {
                    max_time = dist[1];
                }
                graph[i][j] = graph[j][i] = original;
            }
        }
    }

    printf("%d\n", max_time);

    return 0;
}