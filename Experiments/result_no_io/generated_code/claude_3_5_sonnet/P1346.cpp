#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 101
#define INF 1000000000

int N, A, B;
int graph[MAX_N][MAX_N];
int default_route[MAX_N];
int visited[MAX_N];
int queue[MAX_N * MAX_N];
int dist[MAX_N];

void bfs() {
    int front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
    }
    
    queue[rear++] = A;
    visited[A] = 1;
    dist[A] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 1; i <= N; i++) {
            if (graph[current][i]) {
                int switches = (i == default_route[current]) ? 0 : 1;
                if (!visited[i] || dist[i] > dist[current] + switches) {
                    dist[i] = dist[current] + switches;
                    if (!visited[i]) {
                        queue[rear++] = i;
                        visited[i] = 1;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &A, &B);
    
    for (int i = 1; i <= N; i++) {
        int K;
        scanf("%d", &K);
        if (K > 0) {
            scanf("%d", &default_route[i]);
            for (int j = 0; j < K; j++) {
                int destination;
                scanf("%d", &destination);
                graph[i][destination] = 1;
            }
        }
    }
    
    bfs();
    
    if (dist[B] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[B]);
    }
    
    return 0;
}