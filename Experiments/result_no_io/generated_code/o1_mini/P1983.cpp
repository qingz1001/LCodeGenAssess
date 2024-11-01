#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Initialize adjacency list
    int **adj = (int **)malloc((n+1) * sizeof(int *));
    int *adj_size = (int *)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++){
        adj[i] = (int *)malloc(n * sizeof(int));
        adj_size[i] = 0;
    }
    
    // Read trains and build graph
    for(int i=0;i<m;i++){
        int s;
        scanf("%d", &s);
        int *stops = (int *)malloc(s * sizeof(int));
        for(int j=0;j<s;j++) scanf("%d", &stops[j]);
        for(int j=0;j<s-1;j++){
            int u = stops[j];
            int v = stops[j+1];
            adj[u][adj_size[u]++] = v;
        }
        free(stops);
    }
    
    // Compute in-degrees
    int *in_degree = (int *)calloc(n+1, sizeof(int));
    for(int u=1; u<=n; u++) {
        for(int j=0; j<adj_size[u]; j++) {
            int v = adj[u][j];
            in_degree[v]++;
        }
    }
    
    // Initialize remaining nodes
    int remaining = n;
    int level = 0;
    int *queue = (int *)malloc((n+1) * sizeof(int));
    
    while(remaining > 0){
        level++;
        int q_size = 0;
        // Collect nodes with in_degree 0
        for(int u=1; u<=n; u++) {
            if(in_degree[u] == 0){
                queue[q_size++] = u;
                in_degree[u] = -1; // Mark as processed
            }
        }
        if(q_size == 0){
            // No nodes with in-degree 0, but remaining >0, should not happen
            break;
        }
        // Process the queue
        for(int i=0; i<q_size; i++){
            int u = queue[i];
            for(int j=0; j<adj_size[u]; j++){
                int v = adj[u][j];
                in_degree[v]--;
            }
            remaining--;
        }
    }
    
    printf("%d\n", level);
    
    // Free memory
    for(int i=1;i<=n;i++) free(adj[i]);
    free(adj);
    free(adj_size);
    free(in_degree);
    free(queue);
    
    return 0;
}