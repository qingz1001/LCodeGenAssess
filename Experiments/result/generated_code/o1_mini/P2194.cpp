#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXM 300005
#define MOD 1000000007

typedef struct {
    int node;
    int next;
} Edge;

typedef struct {
    int node;
    int state; // 0: first time, push children; 1: all children processed
} StackFrame;

int main(){
    int n;
    scanf("%d", &n);
    unsigned long long w[n+1];
    for(int i=1;i<=n;i++) scanf("%llu", &w[i]);
    int m;
    scanf("%d", &m);
    int *x = (int*)malloc(m * sizeof(int));
    int *y = (int*)malloc(m * sizeof(int));
    int *out_deg = (int*)calloc(n+1, sizeof(int));
    int *in_deg = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<m;i++){
        scanf("%d %d", &x[i], &y[i]);
        out_deg[x[i]]++;
        in_deg[y[i]]++;
    }
    // Allocate adjacency lists
    int *out_edge_start = (int*)malloc((n+2) * sizeof(int));
    out_edge_start[1] = 0;
    for(int i=1;i<=n;i++) out_edge_start[i+1] = out_edge_start[i] + out_deg[i];
    int *adj_original = (int*)malloc(m * sizeof(int));
    // Temporary counters
    int *temp_out = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<m;i++){
        int u = x[i];
        int v = y[i];
        adj_original[out_edge_start[u] + temp_out[u]] = v;
        temp_out[u]++;
    }
    free(temp_out);
    // Build reversed graph
    int *in_edge_start_arr = (int*)malloc((n+2) * sizeof(int));
    in_edge_start_arr[1] = 0;
    for(int i=1;i<=n;i++) in_edge_start_arr[i+1] = in_edge_start_arr[i] + in_deg[i];
    int *adj_rev = (int*)malloc(m * sizeof(int));
    int *temp_in = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<m;i++){
        int u = y[i];
        int v = x[i];
        adj_rev[in_edge_start_arr[u] + temp_in[u]] = v;
        temp_in[u]++;
    }
    free(temp_in);
    free(x);
    free(y);
    // First pass: DFS on original graph to get order
    bool *visited = (bool*)calloc(n+1, sizeof(bool));
    int *order = (int*)malloc(n * sizeof(int));
    int order_cnt = 0;
    // Implement iterative DFS using stack
    StackFrame *stack = (StackFrame*)malloc((n+1) * sizeof(StackFrame));
    int top = 0;
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            stack[top].node = i;
            stack[top].state = 0;
            top++;
            while(top > 0){
                StackFrame frame = stack[top-1];
                if(frame.state == 0){
                    stack[top-1].state = 1;
                    if(!visited[frame.node]){
                        visited[frame.node] = true;
                        for(int e=out_edge_start[frame.node]; e < out_edge_start[frame.node+1]; e++){
                            int neighbor = adj_original[e];
                            if(!visited[neighbor]){
                                stack[top].node = neighbor;
                                stack[top].state = 0;
                                top++;
                            }
                        }
                    }
                }
                else{
                    order[order_cnt++] = stack[top-1].node;
                    top--;
                }
            }
        }
    }
    free(stack);
    free(adj_original);
    free(out_edge_start);
    free(out_deg);
    // Second pass: DFS on reversed graph to assign components
    int *component = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) component[i] = -1;
    int current_comp = 0;
    // Reuse stack
    stack = (StackFrame*)malloc((n+1) * sizeof(StackFrame));
    top = 0;
    for(int i=order_cnt-1;i>=0;i--){
        int u = order[i];
        if(component[u]==-1){
            stack[top].node = u;
            stack[top].state = 0;
            top++;
            while(top > 0){
                StackFrame frame = stack[top-1];
                if(frame.state == 0){
                    stack[top-1].state = 1;
                    component[frame.node] = current_comp;
                    for(int e=in_edge_start_arr[frame.node]; e < in_edge_start_arr[frame.node+1]; e++){
                        int neighbor = adj_rev[e];
                        if(component[neighbor]==-1){
                            stack[top].node = neighbor;
                            stack[top].state = 0;
                            top++;
                        }
                    }
                }
                else{
                    top--;
                }
            }
            current_comp++;
        }
    }
    free(stack);
    free(adj_rev);
    free(in_edge_start_arr);
    free(order);
    free(visited);
    // Now, for each component, find min w and count
    unsigned long long *min_w = (unsigned long long*)malloc(current_comp * sizeof(unsigned long long));
    int *count_min = (int*)malloc(current_comp * sizeof(int));
    for(int i=0;i<current_comp;i++){
        min_w[i] = ~0ULL;
        count_min[i] = 0;
    }
    for(int i=1;i<=n;i++){
        int comp = component[i];
        if(w[i] < min_w[comp]){
            min_w[comp] = w[i];
            count_min[comp] = 1;
        }
        else if(w[i] == min_w[comp]){
            count_min[comp]++;
        }
    }
    // Calculate total cost and number of ways
    unsigned long long total_cost = 0;
    unsigned long long total_ways = 1;
    for(int i=0;i<current_comp;i++){
        total_cost += min_w[i];
        total_ways = (total_ways * (unsigned long long)count_min[i]) % MOD;
    }
    printf("%llu %llu\n", total_cost, total_ways);
    // Free memory
    free(component);
    free(min_w);
    free(count_min);
    return 0;
}