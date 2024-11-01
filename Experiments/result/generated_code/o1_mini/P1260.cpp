#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 1001
#define MAX_EDGES 6001
#define INF 1000000000

typedef struct {
    int to;
    int weight;
} Edge;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Initialize adjacency list
    Edge adj[MAX_NODES][MAX_EDGES];
    int head[MAX_NODES];
    int edge_count[MAX_NODES];
    for(int i=0;i<=n;i++) {
        head[i] = 0;
        edge_count[i] = 0;
    }
    
    // Read constraints T_i - T_j <= b as edges from j to i with weight b
    for(int i=0;i<m;i++){
        int u, v, b;
        scanf("%d %d %d", &u, &v, &b);
        adj[u][edge_count[u]].to = v;
        adj[u][edge_count[u]++].weight = b;
    }
    
    // Add edges for T_i >=0 as T_i >= 0 -> 0 - T_i <=0, edge from i to 0 with weight 0
    for(int i=1;i<=n;i++){
        adj[i][edge_count[i]].to = 0;
        adj[i][edge_count[i]++].weight = 0;
    }
    
    // Initialize distances
    int dist[MAX_NODES];
    for(int i=0;i<=n;i++) dist[i] = INF;
    dist[0] = 0;
    
    // Initialize queue for SPFA
    int queue_nodes[MAX_NODES];
    int front = 0, rear = 0;
    queue_nodes[rear++] = 0;
    
    // In queue flag
    int in_queue_flag[MAX_NODES];
    memset(in_queue_flag, 0, sizeof(in_queue_flag));
    in_queue_flag[0] = 1;
    
    // Count of relaxations
    int count_relax[MAX_NODES];
    memset(count_relax, 0, sizeof(count_relax));
    
    int negative_cycle = 0;
    
    while(front != rear){
        int u = queue_nodes[front++];
        if(front == MAX_NODES) front = 0;
        in_queue_flag[u] = 0;
        
        for(int i=0;i<edge_count[u];i++){
            int v = adj[u][i].to;
            int w = adj[u][i].weight;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                if(!in_queue_flag[v]){
                    queue_nodes[rear++] = v;
                    if(rear == MAX_NODES) rear = 0;
                    in_queue_flag[v] = 1;
                    if(++count_relax[v] > n){
                        negative_cycle = 1;
                        break;
                    }
                }
            }
        }
        if(negative_cycle) break;
    }
    
    if(negative_cycle){
        printf("NO SOLUTION\n");
        return 0;
    }
    
    // Collect T_i
    int T[MAX_NODES];
    for(int i=1;i<=n;i++) T[i] = dist[i];
    
    // Find minimum T_i
    int min_T = T[1];
    for(int i=2;i<=n;i++) if(T[i] < min_T) min_T = T[i];
    
    // Shift T_i to make min_T =0
    for(int i=1;i<=n;i++) T[i] -= min_T;
    
    // Check if all T_i are non-negative after shift
    int valid = 1;
    for(int i=1;i<=n;i++) if(T[i] < 0){
        valid = 0;
        break;
    }
    
    if(!valid){
        printf("NO SOLUTION\n");
        return 0;
    }
    
    // Print T_i
    for(int i=1;i<=n;i++) printf("%d\n", T[i]);
    
    return 0;
}