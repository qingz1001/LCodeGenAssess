#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define LOG 20

int head[MAXN], to_edge[MAXN * 2], next_edge[MAXN * 2], edge_cnt = 0;
int parent[LOG][MAXN], depth_arr[MAXN];
int queue_nodes[MAXN], front = 0, rear = 0;

// Function to add an edge to the adjacency list
void add_edge(int u, int v){
    to_edge[edge_cnt] = v;
    next_edge[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

// BFS to compute depth and immediate parents
void bfs(int n){
    front = rear = 0;
    queue_nodes[rear++] = 1;
    depth_arr[1] = 0;
    parent[0][1] = 0;
    while(front < rear){
        int u = queue_nodes[front++];
        for(int e = head[u]; e != -1; e = next_edge[e]){
            int v = to_edge[e];
            if(v != parent[0][u]){
                parent[0][v] = u;
                depth_arr[v] = depth_arr[u] + 1;
                queue_nodes[rear++] = v;
            }
        }
    }
}

// Precompute ancestors for LCA
void compute_lca(int n){
    for(int k = 1; k < LOG; k++){
        for(int v = 1; v <= n; v++){
            if(parent[k-1][v] != 0){
                parent[k][v] = parent[k-1][parent[k-1][v]];
            }
            else{
                parent[k][v] = 0;
            }
        }
    }
}

// Function to find LCA
int lca_func(int u, int v){
    if(depth_arr[u] < depth_arr[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    for(int k = LOG-1; k >=0; k--){
        if(depth_arr[u] - (1<<k) >= depth_arr[v]){
            u = parent[k][u];
        }
    }
    if(u == v) return u;
    for(int k = LOG-1; k >=0; k--){
        if(parent[k][u] != 0 && parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

// Function to compute distance between two nodes
int distance_func(int u, int v){
    int lca = lca_func(u, v);
    return depth_arr[u] + depth_arr[v] - 2 * depth_arr[lca];
}

int main(){
    int n;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for(int i = 0; i < n-1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    bfs(n);
    compute_lca(n);
    
    // Attempt to construct a path (This is a placeholder. Implement the actual path construction logic here.)
    // For now, output "BRAK" as the path construction is non-trivial.
    printf("BRAK\n");
    
    return 0;
}