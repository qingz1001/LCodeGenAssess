#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define LOG 19

typedef struct Edge {
    int to;
    int next;
} Edge;

Edge edges[600010];
int head[MAXN];
int edge_cnt = 0;

int parent[LOG][MAXN];
int depth_node[MAXN];
long long counts[MAXN];
int a_seq[MAXN];
int n;

// Function to add edge to the adjacency list
void add_edge(int u, int v){
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

// DFS to set depth and immediate parent
void dfs(int u, int p_u){
    parent[0][u] = p_u;
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(v != p_u){
            depth_node[v] = depth_node[u] + 1;
            dfs(v, u);
        }
    }
}

// Preprocess to fill parent[k][u]
void preprocess(){
    for(int k =1; k < LOG; k++){
        for(int u =1; u <=n; u++){
            if(parent[k-1][u] != -1){
                parent[k][u] = parent[k-1][parent[k-1][u]];
            }
            else{
                parent[k][u] = -1;
            }
        }
    }
}

// LCA using binary lifting
int lca_func(int u, int v){
    if(depth_node[u] < depth_node[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    // Bring u to the same depth as v
    for(int k = LOG-1; k >=0; k--){
        if(parent[k][u] != -1 && depth_node[parent[k][u]] >= depth_node[v]){
            u = parent[k][u];
        }
    }
    if(u == v){
        return u;
    }
    // Move both u and v up until their parents are the same
    for(int k = LOG-1; k >=0; k--){
        if(parent[k][u] != -1 && parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

// DFS to accumulate counts
long long dfs_counts(int u, int p_u){
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(v != p_u){
            counts[u] += dfs_counts(v, u);
        }
    }
    return counts[u];
}

int main(){
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for(int i =1; i<=n; i++) scanf("%d", &a_seq[i]);
    for(int i =1; i<n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    // Initialize depth and parent
    depth_node[1] = 0;
    dfs(1, -1);
    preprocess();
    // Process each consecutive pair
    for(int i=1; i<n; i++){
        int u = a_seq[i];
        int v = a_seq[i+1];
        int lca = lca_func(u, v);
        counts[u]++;
        counts[v]++;
        counts[lca] -=2;
    }
    // Accumulate counts
    dfs_counts(1, -1);
    // Output the counts
    for(int i=1; i<=n; i++) printf("%lld\n", counts[i]);
    return 0;
}