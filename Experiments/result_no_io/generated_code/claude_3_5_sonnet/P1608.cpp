#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 2000
#define INF INT_MAX

int N, E;
int dist[MAX_N + 1];
long long paths[MAX_N + 1];
int graph[MAX_N + 1][MAX_N + 1];

void dijkstra() {
    int visited[MAX_N + 1] = {0};
    
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        paths[i] = 0;
    }
    
    dist[1] = 0;
    paths[1] = 1;
    
    for (int i = 1; i <= N; i++) {
        int u = -1;
        int min_dist = INF;
        
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        for (int v = 1; v <= N; v++) {
            if (graph[u][v] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    paths[v] = paths[u];
                } else if (dist[u] + graph[u][v] == dist[v]) {
                    paths[v] += paths[u];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &E);
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = INF;
        }
    }
    
    for (int i = 0; i < E; i++) {
        int I, J, C;
        scanf("%d %d %d", &I, &J, &C);
        if (C < graph[I][J]) {
            graph[I][J] = C;
        }
    }
    
    dijkstra();
    
    if (dist[N] == INF) {
        printf("No answer\n");
    } else {
        printf("%d %lld\n", dist[N], paths[N]);
    }
    
    return 0;
}