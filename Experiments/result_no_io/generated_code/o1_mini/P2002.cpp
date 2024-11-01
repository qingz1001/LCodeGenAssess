#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int b;
    int e;
} Edge;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    int *ptr_f = (int*)calloc(n+1, sizeof(int));
    int *ptr_r = (int*)calloc(n+1, sizeof(int));
    
    for(int i=0;i<m;i++){
        scanf("%d %d", &edges[i].b, &edges[i].e);
        ptr_f[edges[i].b-1]++;
        ptr_r[edges[i].e-1]++;
    }
    
    for(int i=1;i<=n;i++){
        ptr_f[i] += ptr_f[i-1];
        ptr_r[i] += ptr_r[i-1];
    }
    
    int *adj_f = (int*)malloc(sizeof(int)*m);
    int *adj_r = (int*)malloc(sizeof(int)*m);
    int *temp_f = (int*)malloc(sizeof(int)*n);
    int *temp_r = (int*)malloc(sizeof(int)*n);
    memcpy(temp_f, ptr_f, sizeof(int)*n);
    memcpy(temp_r, ptr_r, sizeof(int)*n);
    
    for(int i=0;i<m;i++){
        int b = edges[i].b -1;
        int e = edges[i].e -1;
        adj_f[temp_f[b]++] = e;
        adj_r[temp_r[e]++] = b;
    }
    
    free(edges);
    free(temp_f);
    free(temp_r);
    free(ptr_f);
    free(ptr_r);
    
    // First pass: order
    int *vis = (int*)calloc(n, sizeof(int));
    int *order = (int*)malloc(sizeof(int)*n);
    int top = 0;
    int *stk = (int*)malloc(sizeof(int)*n);
    int stk_ptr = 0;
    
    for(int u=0; u<n; u++){
        if(!vis[u]){
            stk[stk_ptr++] = u;
            vis[u] = 1;
            while(stk_ptr >0){
                int v = stk[stk_ptr-1];
                // Find first unvisited neighbor
                int start = 0;
                // Assuming adj_f is built with prefix sums
                // Not storing adjacency list sizes, so need to reconstruct
                // Instead, use temporary variables
                // Not efficient, adjust the approach
                // Alternative: rebuild adj_f with end pointers
                // To simplify, use separate arrays for start indices
                // Not done, implement recursive-like iterative DFS
                // Reimplement first pass
                break;
            }
        }
    }
    // Instead of above incomplete first pass, implement proper Kosaraju's
    
    // Implement Kosaraju's first pass
    // Reset vis
    memset(vis, 0, sizeof(int)*n);
    int *stack = (int*)malloc(sizeof(int)*n);
    int stack_ptr = 0;
    for(int u=0; u<n; u++){
        if(!vis[u]){
            stack[stack_ptr++] = u;
            while(stack_ptr >0){
                int node = stack[stack_ptr-1];
                if(!vis[node]){
                    vis[node] = 1;
                    // Push all neighbors
                    for(int i=ptr_f[node]; i<(node < n-1 ? ptr_f[node+1] : m); i++){
                        int neighbor = adj_f[i];
                        if(!vis[neighbor]){
                            stack[stack_ptr++] = neighbor;
                        }
                    }
                }
                else{
                    order[top++] = stack[--stack_ptr];
                }
            }
        }
    }
    
    // Second pass
    int *component = (int*)malloc(sizeof(int)*n);
    memset(component, -1, sizeof(int)*n);
    int current_component = 0;
    
    for(int i=top-1;i>=0;i--){
        int u = order[i];
        if(component[u]==-1){
            stack[stack_ptr++] = u;
            component[u] = current_component;
            while(stack_ptr >0){
                int node = stack[stack_ptr-1];
                stack_ptr--;
                // Push all neighbors in reverse graph
                for(int j=ptr_r[node]; j<(node < n-1 ? ptr_r[node+1] : m); j++){
                    int neighbor = adj_r[j];
                    if(component[neighbor]==-1){
                        component[neighbor] = current_component;
                        stack[stack_ptr++] = neighbor;
                    }
                }
            }
            current_component++;
        }
    }
    
    // Count in-degrees
    int *in_degree = (int*)calloc(current_component, sizeof(int));
    for(int u=0; u<n; u++){
        for(int i=ptr_f[u]; i<(u < n-1 ? ptr_f[u+1] : m); i++){
            int v = adj_f[i];
            if(component[u] != component[v]){
                in_degree[component[v]] = 1;
            }
        }
    }
    
    int count =0;
    for(int i=0;i<current_component;i++) if(in_degree[i]==0) count++;
    printf("%d\n", count);
    
    // Free memory
    free(adj_f);
    free(adj_r);
    free(stack);
    free(order);
    free(vis);
    free(component);
    free(in_degree);
    
    return 0;
}