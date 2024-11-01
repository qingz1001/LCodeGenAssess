#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

int n;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int dist[MAX_N];

int prim() {
    int i, j, min, minIndex, totalCost = 0;
    
    for (i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    
    dist[0] = 0;
    
    for (i = 0; i < n; i++) {
        min = INT_MAX;
        minIndex = -1;
        
        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                minIndex = j;
            }
        }
        
        visited[minIndex] = 1;
        totalCost += min;
        
        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[minIndex][j] < dist[j]) {
                dist[j] = graph[minIndex][j];
            }
        }
    }
    
    return totalCost;
}

int main() {
    int i, j;
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("%d\n", prim());
    
    return 0;
}