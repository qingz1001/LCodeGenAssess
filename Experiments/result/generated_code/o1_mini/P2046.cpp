#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Define the maximum number of nodes
#define MAX_NODES 251001
#define MAX_EDGES 4000000

typedef struct Edge {
    int to;
    long long cap;
    int next;
} Edge;

Edge edges[MAX_EDGES];
int head[MAX_NODES];
int edge_cnt = 0;

// Function to add edges to the graph
void add_edge(int from, int to, long long cap) {
    edges[edge_cnt].to = to;
    edges[edge_cnt].cap = cap;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
    
    // Add reverse edge with 0 capacity
    edges[edge_cnt].to = from;
    edges[edge_cnt].cap = 0;
    edges[edge_cnt].next = head[to];
    head[to] = edge_cnt++;
}

// BFS to build levels
int level_num[MAX_NODES];
int queue_nodes[MAX_NODES];
int bfs(int S, int T, int node_cnt) {
    memset(level_num, -1, sizeof(int) * (node_cnt + 1));
    int head_q = 0, tail_q = 0;
    queue_nodes[tail_q++] = S;
    level_num[S] = 0;
    while (head_q < tail_q) {
        int u = queue_nodes[head_q++];
        for(int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            if(edges[i].cap > 0 && level_num[v] == -1){
                level_num[v] = level_num[u] + 1;
                queue_nodes[tail_q++] = v;
                if(v == T) return 1;
            }
        }
    }
    return level_num[T] != -1;
}

// DFS to find blocking flows
long long dfs(int u, int T, long long flow) {
    if(u == T) return flow;
    long long pushed = 0;
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(edges[i].cap > 0 && level_num[v] == level_num[u] + 1){
            long long tmp = dfs(v, T, flow < edges[i].cap ? flow : edges[i].cap);
            if(tmp > 0){
                edges[i].cap -= tmp;
                edges[i^1].cap += tmp;
                pushed += tmp;
                flow -= tmp;
                if(flow == 0) break;
            }
        }
    }
    return pushed;
}

// Dinic's algorithm
long long max_flow(int S, int T, int node_cnt){
    long long flow = 0;
    while(bfs(S, T, node_cnt)){
        flow += dfs(S, T, LLONG_MAX);
    }
    return flow;
}

int main(){
    int n;
    scanf("%d", &n);
    int total_roads = 4 * n * (n +1);
    
    // Initialize head
    memset(head, -1, sizeof(head));
    
    // Function to map grid to node index
    #define NODE(i,j) ((i)*(n+1)+(j))
    
    // Read East->West flows
    long long* east = (long long*)malloc(sizeof(long long)*n*(n+1));
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &east[i]);
    
    // Read North->South flows
    long long* south = (long long*)malloc(sizeof(long long)*n*(n+1));
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &south[i]);
    
    // Read West->East flows
    long long* west = (long long*)malloc(sizeof(long long)*n*(n+1));
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &west[i]);
    
    // Read South->North flows
    long long* north = (long long*)malloc(sizeof(long long)*n*(n+1));
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &north[i]);
    
    // Build the graph
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            int current = NODE(i,j);
            // East
            if(j < n){
                int to = NODE(i,j+1);
                long long f1 = east[i*n + j];
                long long f2 = west[i*n + j];
                add_edge(current, to, f1);
                add_edge(to, current, f2);
            }
            // South
            if(i < n){
                int to = NODE(i+1,j);
                long long f1 = south[i*n + j];
                long long f2 = north[i*n + j];
                add_edge(current, to, f1);
                add_edge(to, current, f2);
            }
        }
    }
    
    // Define source and sink
    int S = NODE(0,0);
    int T = NODE(n,n);
    
    // Calculate max flow which is min cut
    long long result = max_flow(S, T, (n+1)*(n+1)-1);
    
    // Print the result rounded to the nearest integer
    printf("%lld\n", result);
    
    // Free allocated memory
    free(east);
    free(south);
    free(west);
    free(north);
    
    return 0;
}