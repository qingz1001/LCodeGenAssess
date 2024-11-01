#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXW 6000
#define INF 0x3f3f3f3f

int N, W;
int graph[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];

void init() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = INF;
        }
        graph[i][i] = 0;
    }
}

int prim() {
    int total = 0;
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
        total += min_dist;
        
        for (int v = 1; v <= N; v++) {
            if (!visited[v] && graph[u][v] < dist[v]) {
                dist[v] = graph[u][v];
            }
        }
    }
    
    return total;
}

int main() {
    scanf("%d %d", &N, &W);
    init();
    
    for (int w = 0; w < W; w++) {
        int u, v, len;
        scanf("%d %d %d", &u, &v, &len);
        if (len < graph[u][v]) {
            graph[u][v] = graph[v][u] = len;
        }
        
        int result = prim();
        printf("%d\n", result);
    }
    
    return 0;
}