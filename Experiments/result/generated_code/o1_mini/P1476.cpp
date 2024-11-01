#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 105

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    Edge* graph[MAX_NODES];
    for(int i=0;i<MAX_NODES;i++) graph[i] = NULL;
    
    int u, v, w;
    int max_node = 0;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &u, &v, &w);
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        newEdge->to = v;
        newEdge->weight = w;
        newEdge->next = graph[u];
        graph[u] = newEdge;
        if(v > max_node) max_node = v;
        if(u > max_node) max_node = u;
    }
    
    // Topological sort
    int in_degree[MAX_NODES];
    memset(in_degree, 0, sizeof(in_degree));
    for(int i=1;i<=max_node;i++){
        Edge* ptr = graph[i];
        while(ptr){
            in_degree[ptr->to]++;
            ptr = ptr->next;
        }
    }
    
    // Initialize
    int queue[MAX_NODES], front=0, rear=0;
    for(int i=1;i<=max_node;i++) {
        if(in_degree[i]==0){
            queue[rear++] = i;
        }
    }
    
    // Longest path
    long long dist[MAX_NODES];
    memset(dist, 0, sizeof(dist));
    int predecessor[MAX_NODES];
    memset(predecessor, -1, sizeof(predecessor));
    
    while(front < rear){
        int u = queue[front++];
        Edge* ptr = graph[u];
        while(ptr){
            if(dist[ptr->to] < dist[u] + ptr->weight){
                dist[ptr->to] = dist[u] + ptr->weight;
                predecessor[ptr->to] = u;
            }
            in_degree[ptr->to]--;
            if(in_degree[ptr->to]==0){
                queue[rear++] = ptr->to;
            }
            ptr = ptr->next;
        }
    }
    
    // Find the maximum distance
    long long max_dist = 0;
    int end_node = 1;
    for(int i=1;i<=max_node;i++){
        if(dist[i] > max_dist){
            max_dist = dist[i];
            end_node = i;
        }
    }
    
    // Reconstruct the path
    int path[MAX_NODES];
    int path_len =0;
    int current = end_node;
    while(current != -1){
        path[path_len++] = current;
        current = predecessor[current];
    }
    
    // Collect unique nodes and sort
    int nodes_in_path[MAX_NODES];
    int count =0;
    for(int i=path_len-1;i>=0;i--){
        nodes_in_path[count++] = path[i];
    }
    // Sort
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(nodes_in_path[i] > nodes_in_path[j]){
                int tmp = nodes_in_path[i];
                nodes_in_path[i] = nodes_in_path[j];
                nodes_in_path[j] = tmp;
            }
        }
    }
    
    // Print the results
    printf("%lld\n", max_dist);
    for(int i=0;i<count;i++){
        printf("%d", nodes_in_path[i]);
        if(i != count-1) printf(" ");
    }
    printf("\n");
    
    // Free memory
    for(int i=0;i<=max_node;i++){
        Edge* ptr = graph[i];
        while(ptr){
            Edge* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    
    return 0;
}