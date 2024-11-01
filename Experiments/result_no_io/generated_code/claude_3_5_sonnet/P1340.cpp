#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 201
#define INF 1000000000

int N, W;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

void init_graph() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
}

int prim() {
    int total_cost = 0;
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    
    dist[1] = 0;
    
    for (int i = 1; i <= N; i++) {
        int min_dist = INF, u = -1;
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) return -1;
        
        visited[u] = 1;
        total_cost += dist[u];
        
        for (int v = 1; v <= N; v++) {
            if (!visited[v] && graph[u][v] < dist[v]) {
                dist[v] = graph[u][v];
            }
        }
    }
    
    return total_cost;
}

int main() {
    scanf("%d %d", &N, &W);
    init_graph();
    
    for (int week = 1; week <= W; week++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (w < graph[u][v]) {
            graph[u][v] = graph[v][u] = w;
        }
        
        int result = prim();
        printf("%d\n", result);
    }
    
    return 0;
}