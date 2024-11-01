#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 301
#define INF 0x3f3f3f3f

int n;
int W[MAX_N];
int P[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

int prim() {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    
    dist[0] = 0;
    int total_cost = 0;
    
    for (int i = 0; i <= n; i++) {
        int min_dist = INF;
        int u = -1;
        
        for (int j = 0; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        total_cost += min_dist;
        
        for (int v = 0; v <= n; v++) {
            if (!visited[v]) {
                if (u == 0) {
                    if (W[v] < dist[v]) {
                        dist[v] = W[v];
                    }
                } else if (v == 0) {
                    if (W[u] < dist[v]) {
                        dist[v] = W[u];
                    }
                } else {
                    if (P[u-1][v-1] < dist[v]) {
                        dist[v] = P[u-1][v-1];
                    }
                }
            }
        }
    }
    
    return total_cost;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &W[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    
    int result = prim();
    printf("%d\n", result);
    
    return 0;
}