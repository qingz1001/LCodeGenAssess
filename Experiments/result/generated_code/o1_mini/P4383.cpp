#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Structure to represent an edge
typedef struct {
    int u;
    int v;
    int64_t w;
} Edge;

// Comparator for sorting edges by weight ascending
int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if(ea->w < eb->w) return -1;
    if(ea->w > eb->w) return 1;
    return 0;
}

// Maximum between two int64_t
inline int64_t max_val(int64_t a, int64_t b){
    return a > b ? a : b;
}

#define MAXN 300005

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    Edge* edges = (Edge*)malloc((N-1) * sizeof(Edge));
    // Adjacency list
    int* head = (int*)calloc(N+1, sizeof(int));
    int* to = (int*)malloc(2*(N-1)*sizeof(int));
    int* weight = (int64_t*)malloc(2*(N-1)*sizeof(int64_t));
    int idx = 0;
    for(int i=0;i<N-1;i++){
        int x, y;
        int w;
        scanf("%d %d %d", &x, &y, &w);
        edges[i].u = x;
        edges[i].v = y;
        edges[i].w = w;
        // Building adjacency list
        to[idx] = y;
        weight[idx] = w;
        head[x]++;
        idx++;
        to[idx] = x;
        weight[idx] = w;
        head[y]++;
        idx++;
    }
    // Convert head to actual adjacency list indices
    int* ptr = (int*)malloc((N+1) * sizeof(int));
    ptr[1] = 0;
    for(int i=2;i<=N;i++) ptr[i] = ptr[i-1] + head[i-1];
    // Reset head
    for(int i=1;i<=N;i++) head[i] = 0;
    // Fill adjacency list
    for(int i=0;i<N-1;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int64_t w = edges[i].w;
        int pos = ptr[u] + head[u];
        to[pos] = v;
        weight[pos] = w;
        head[u]++;
        pos = ptr[v] + head[v];
        to[pos] = u;
        weight[pos] = w;
        head[v]++;
    }
    free(edges);
    free(ptr);
    // Collect negative edges
    Edge* neg_edges = (Edge*)malloc((N-1) * sizeof(Edge));
    int neg_count = 0;
    for(int i=0;i<N-1;i++){
        // As edges are duplicated in adjacency list, skip duplicates
        // To avoid this complexity, use original edge list
        // So we need to read edges again
    }
    // Re-read original edges
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d", &N, &K);
    edges = (Edge*)malloc((N-1) * sizeof(Edge));
    int edge_idx = 0;
    for(int i=0;i<N-1;i++){
        int x, y;
        int w;
        scanf("%d %d %d", &x, &y, &w);
        edges[i].u = x;
        edges[i].v = y;
        edges[i].w = w;
        if(w < 0){
            neg_edges[neg_count++] = edges[i];
        }
    }
    // Sort negative edges by weight ascending
    if(neg_count >0){
        qsort(neg_edges, neg_count, sizeof(Edge), cmp);
    }
    // Replace up to K most negative edges with zero
    int replace = K < neg_count ? K : neg_count;
    for(int i=0;i<replace;i++) {
        neg_edges[i].w = 0;
    }
    // Update the weights in the adjacency list
    // Create a map for edge weights
    // Since the tree is undirected and edges are unique, we can use a trick
    // Reconstruct adjacency list with updated weights
    // Reinitialize head
    for(int i=1;i<=N;i++) head[i] = 0;
    // Count degrees again
    for(int i=0;i<N-1;i++){
        head[edges[i].u]++;
        head[edges[i].v]++;
    }
    // Allocate adjacency lists
    int** adj = (int**)malloc((N+1) * sizeof(int*));
    int64_t** adj_w = (int64_t**)malloc((N+1) * sizeof(int64_t*));
    for(int i=1;i<=N;i++){
        adj[i] = (int*)malloc(head[i] * sizeof(int));
        adj_w[i] = (int64_t*)malloc(head[i] * sizeof(int64_t));
        head[i] = 0;
    }
    // Assign weights, replacing negative edges set to zero
    for(int i=0;i<N-1;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int64_t w = edges[i].w;
        // Check if this edge was replaced
        for(int j=0;j<replace;j++){
            if((neg_edges[j].u == u && neg_edges[j].v == v) || (neg_edges[j].u == v && neg_edges[j].v == u)){
                w = 0;
                break;
            }
        }
        adj[u][head[u]] = v;
        adj_w[u][head[u]] = w;
        head[u]++;
        adj[v][head[v]] = u;
        adj_w[v][head[v]] = w;
        head[v]++;
    }
    free(edges);
    free(neg_edges);
    // Now perform DFS to find maximum path sum
    int64_t global_max = -__INT64_MAX__;
    // We need to avoid stack overflow, use iterative DFS
    int* stack = (int*)malloc((N+1) * sizeof(int));
    int top = -1;
    // To store maximum path from node
    int64_t* dp = (int64_t*)malloc((N+1) * sizeof(int64_t));
    // To store visited
    int* visited_flag = (int*)calloc(N+1, sizeof(int));
    // To store children iterator
    int* child_idx = (int*)calloc(N+1, sizeof(int));
    // Initialize
    stack[++top] = 1;
    while(top >=0){
        int u = stack[top];
        if(!visited_flag[u]){
            visited_flag[u] = 1;
            // Push children to stack
            for(int i=0;i<head[u];i++){
                int v = adj[u][i];
                if(!visited_flag[v]){
                    stack[++top] = v;
                }
            }
        }
        else{
            // Post-order processing
            top--;
            // Compute dp[u]
            int64_t first = 0, second = 0;
            for(int i=0;i<head[u];i++){
                int v = adj[u][i];
                int64_t w = adj_w[u][i];
                if(dp[v] + w > first){
                    second = first;
                    first = dp[v] + w;
                }
                else if(dp[v] + w > second){
                    second = dp[v] + w;
                }
            }
            dp[u] = first;
            // Update global_max with first + second
            if(first + second > global_max){
                global_max = first + second;
            }
        }
    }
    printf("%lld\n", global_max);
    // Free memory
    for(int i=1;i<=N;i++){
        free(adj[i]);
        free(adj_w[i]);
    }
    free(adj);
    free(adj_w);
    free(head);
    free(to);
    free(weight);
    free(ptr);
    free(stack);
    free(dp);
    free(visited_flag);
    free(child_idx);
    return 0;
}