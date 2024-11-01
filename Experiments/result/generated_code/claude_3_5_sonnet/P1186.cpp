#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_M 500500

int N, M;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

void dijkstra(int start) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < N - 1; count++) {
        int min = INT_MAX, min_index;
        for (int v = 1; v <= N; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                min_index = v;
            }
        }

        visited[min_index] = 1;

        for (int v = 1; v <= N; v++) {
            if (!visited[v] && graph[min_index][v] && 
                dist[min_index] != INT_MAX && 
                dist[min_index] + graph[min_index][v] < dist[v]) {
                dist[v] = dist[min_index] + graph[min_index][v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int A, B, V;
        scanf("%d %d %d", &A, &B, &V);
        graph[A][B] = graph[B][A] = V;
    }

    int max_time = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (graph[i][j] > 0) {
                int temp = graph[i][j];
                graph[i][j] = graph[j][i] = 0;
                dijkstra(N);
                if (dist[1] > max_time) {
                    max_time = dist[1];
                }
                graph[i][j] = graph[j][i] = temp;
            }
        }
    }

    printf("%d\n", max_time);

    return 0;
}