#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int *neighbors;
    int degree;
    int size;
} Node;

int main(){
    int n, t, m;
    scanf("%d %d %d", &n, &t, &m);
    
    // Initialize nodes
    Node *nodes = (Node*)malloc((n+1)*sizeof(Node));
    for(int i=1;i<=n;i++){
        nodes[i].neighbors = NULL;
        nodes[i].degree = 0;
        nodes[i].size = 0;
    }
    
    // Read edges
    int a, b;
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &a, &b);
        nodes[a].degree++;
        nodes[b].degree++;
    }
    
    // Allocate neighbors
    for(int i=1;i<=n;i++){
        if(nodes[i].degree >0){
            nodes[i].neighbors = (int*)malloc(nodes[i].degree * sizeof(int));
            nodes[i].size =0;
        }
    }
    
    // Reset degrees to use as indices
    for(int i=1;i<=n;i++) nodes[i].degree =0;
    
    // Read edges again to fill neighbors
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d %d", &n, &t, &m);
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &a, &b);
        nodes[a].neighbors[nodes[a].degree++] = b;
        nodes[b].neighbors[nodes[b].degree++] = a;
    }
    
    // BFS to find path from m to t
    bool *visited = (bool*)calloc(n+1, sizeof(bool));
    int *parent = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) parent[i] = -1;
    
    // Implement BFS
    int *queue = (int*)malloc((n+1)*sizeof(int));
    int front=0, rear=0;
    queue[rear++] = m;
    visited[m] = true;
    
    while(front < rear){
        int current = queue[front++];
        if(current == t) break;
        for(int i=0;i<nodes[current].degree;i++){
            int neighbor = nodes[current].neighbors[i];
            if(!visited[neighbor]){
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue[rear++] = neighbor;
            }
        }
    }
    
    // Trace the path from t to m
    bool *onPath = (bool*)calloc(n+1, sizeof(bool));
    int node = t;
    while(node != -1){
        onPath[node] = true;
        node = parent[node];
    }
    
    // Count leaves not on path
    int leafCount =0;
    for(int i=1;i<=n;i++){
        if(nodes[i].degree ==1 && !onPath[i]){
            leafCount++;
        }
    }
    
    printf("%d\n", leafCount);
    
    // Free memory
    for(int i=1;i<=n;i++) {
        if(nodes[i].neighbors) free(nodes[i].neighbors);
    }
    free(nodes);
    free(visited);
    free(parent);
    free(queue);
    free(onPath);
    return 0;
}