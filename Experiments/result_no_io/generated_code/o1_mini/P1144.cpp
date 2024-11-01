#include <stdio.h>
#include <stdlib.h>

#define MOD 100003

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Allocate memory for adjacency list
    Edge** adj = (Edge**)calloc(N+1, sizeof(Edge*));
    if(!adj){
        return 1;
    }
    
    // Read edges
    for(int i=0;i<M;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        // Add y to x
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = y;
        e1->next = adj[x];
        adj[x] = e1;
        // Add x to y
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = x;
        e2->next = adj[y];
        adj[y] = e2;
    }
    
    // Initialize distance and count
    int* distance = (int*)malloc((N+1)*sizeof(int));
    int* count = (int*)malloc((N+1)*sizeof(int));
    for(int i=1;i<=N;i++){
        distance[i] = -1;
        count[i] = 0;
    }
    
    // Initialize queue
    int* queue = (int*)malloc((N+1)*sizeof(int));
    int front = 0, rear = 0;
    
    // Start BFS from node 1
    distance[1] = 0;
    count[1] = 1;
    queue[rear++] = 1;
    
    while(front < rear){
        int u = queue[front++];
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(distance[v] == -1){
                distance[v] = distance[u] + 1;
                count[v] = count[u];
                queue[rear++] = v;
            }
            else if(distance[v] == distance[u] + 1){
                count[v] = (count[v] + count[u]) % MOD;
            }
        }
    }
    
    // Print results
    for(int i=1;i<=N;i++){
        if(distance[i] == -1){
            printf("0\n");
        }
        else{
            printf("%d\n", count[i]);
        }
    }
    
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(adj);
    free(distance);
    free(count);
    free(queue);
    
    return 0;
}