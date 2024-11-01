#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 301
#define INF 1000000000

int n;
int W[MAX_N];
int P[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

int prim() {
    int i, j, min_cost, min_index, total_cost = 0;
    
    for (i = 0; i < n; i++) {
        dist[i] = W[i];
        visited[i] = 0;
    }
    
    for (i = 0; i < n; i++) {
        min_cost = INF;
        min_index = -1;
        
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_cost) {
                min_cost = dist[j];
                min_index = j;
            }
        }
        
        if (min_index == -1) break;
        
        visited[min_index] = 1;
        total_cost += min_cost;
        
        for (j = 0; j < n; j++) {
            if (!visited[j] && P[min_index][j] < dist[j]) {
                dist[j] = P[min_index][j];
            }
        }
    }
    
    return total_cost;
}

int main() {
    int i, j;
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        scanf("%d", &W[i]);
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    
    printf("%d\n", prim());
    
    return 0;
}