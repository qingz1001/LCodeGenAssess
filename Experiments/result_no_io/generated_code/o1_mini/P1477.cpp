#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

typedef struct {
    int to;
    int next;
} Edge;

int adj_head_arr[MAXN];
int radj_head_arr[MAXN];
Edge adj_edges[MAXM];
Edge radj_edges[MAXM];
int adj_size = 0, radj_size = 0;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    memset(adj_head_arr, -1, sizeof(int)*(n+1));
    memset(radj_head_arr, -1, sizeof(int)*(n+1));
    int a, b;
    for(int i=0;i<m;i++){
        scanf("%d %d", &a, &b);
        adj_edges[adj_size].to = b;
        adj_edges[adj_size].next = adj_head_arr[a];
        adj_head_arr[a] = adj_size++;
        radj_edges[radj_size].to = a;
        radj_edges[radj_size].next = radj_head_arr[b];
        radj_head_arr[b] = radj_size++;
    }
    // First pass: DFS to get order
    int *visited = (int*)calloc(n+1, sizeof(int));
    int *order = (int*)malloc(sizeof(int)*n);
    int order_size =0;
    int *stack = (int*)malloc(sizeof(int)*(n+1));
    int top = -1;
    for(int u=1; u<=n; u++){
        if(!visited[u]){
            stack[++top] = u;
            while(top != -1){
                int node = stack[top];
                if(node < 0){
                    order[order_size++] = -node;
                    top--;
                    continue;
                }
                if(visited[node]){
                    top--;
                    continue;
                }
                visited[node] =1;
                stack[top] = -node;
                for(int e = adj_head_arr[node]; e != -1; e = adj_edges[e].next){
                    int v = adj_edges[e].to;
                    if(!visited[v]){
                        stack[++top] = v;
                    }
                }
            }
        }
    }
    free(stack);
    // Second pass: DFS on reverse graph
    int *comp = (int*)malloc(sizeof(int)*(n+1));
    memset(comp, -1, sizeof(int)*(n+1));
    int num_comp =0;
    stack = (int*)malloc(sizeof(int)*(n+1));
    top = -1;
    for(int i=order_size-1;i>=0;i--){
        int u = order[i];
        if(comp[u]==-1){
            stack[++top] = u;
            comp[u] = num_comp;
            while(top != -1){
                int node = stack[top--];
                for(int e = radj_head_arr[node]; e != -1; e = radj_edges[e].next){
                    int v = radj_edges[e].to;
                    if(comp[v]==-1){
                        comp[v] = num_comp;
                        stack[++top] = v;
                    }
                }
            }
            num_comp++;
        }
    }
    free(order);
    free(visited);
    free(radj_edges);
    free(adj_edges);
    // Check for cycles
    int *comp_size_arr = (int*)calloc(num_comp, sizeof(int));
    int *has_self_loop = (int*)calloc(n+1, sizeof(int));
    // Rebuild adj list for second pass
    // No need, use original adj_head_arr
    // Count component sizes and self-loops
    for(int u=1; u<=n; u++){
        comp_size_arr[comp[u]]++;
        for(int e = adj_head_arr[u]; e != -1; e = adj_edges[e].next){
            if(adj_edges[e].to == u){
                has_self_loop[u] =1;
            }
        }
    }
    // Now, for each component, check if it has cycle
    // If size >1 or has self-loop
    // Prepare list of nodes per component
    int *comp_nodes = (int*)malloc(sizeof(int)*n);
    int *comp_indices = (int*)calloc(num_comp, sizeof(int));
    for(int u=1; u<=n; u++){
        int cid = comp[u];
        comp_nodes[cid * n + comp_indices[cid]++] = u;
    }
    // Prepare for BFS
    int *level = (int*)malloc(sizeof(int)*(n+1));
    memset(level, -1, sizeof(int)*(n+1));
    // Initialize global GCD
    int global_gcd =0;
    // Function to compute GCD
    auto gcd_func = [](int a, int b) -> int{
        while(b){
            int tmp = a % b;
            a = b;
            b = tmp;
        }
        return a;
    };
    // Iterate over each component
    for(int cid=0; cid<num_comp; cid++){
        if(comp_size_arr[cid] >1){
            // Has cycle
        }
        else{
            // size ==1, check self-loop
            int u = comp_nodes[cid * n];
            if(has_self_loop[u]){
                // Has cycle
            }
            else{
                continue;
            }
        }
        // BFS to assign levels and compute GCD
        // Get all nodes in this component
        // Find root
        int root = comp_nodes[cid * n];
        // Reset queue
        int front_q =0, rear_q =0;
        // Initialize
        level[root] =0;
        // Initialize queue
        int *queue = (int*)malloc(sizeof(int)*n);
        queue[rear_q++] = root;
        while(front_q < rear_q){
            int u = queue[front_q++];
            for(int e = adj_head_arr[u]; e != -1; e = adj_edges[e].next){
                int v = adj_edges[e].to;
                if(comp[v] != cid){
                    continue;
                }
                if(level[v]==-1){
                    level[v] = level[u] +1;
                    queue[rear_q++] = v;
                }
                else{
                    int diff = level[v] - level[u] -1;
                    if(diff <0){
                        diff = -diff;
                    }
                    if(diff >0){
                        global_gcd = gcd_func(global_gcd, diff);
                    }
                }
            }
        }
        // Reset levels for this component
        for(int i=0; i<comp_size_arr[cid]; i++){
            int u = comp_nodes[cid * n +i];
            level[u] = -1;
        }
        free(queue);
    }
    free(comp_nodes);
    free(comp_size_arr);
    free(has_self_loop);
    free(comp);
    free(adj_head_arr);
    // Now, decide k_max and k_min
    if(global_gcd ==0){
        // No cycles, any k >=3
        if(n >=3){
            printf("%d %d", n, 3);
        }
        else{
            printf("-1");
        }
    }
    else{
        if(global_gcd <3){
            printf("-1");
        }
        else{
            // Find smallest divisor of global_gcd >=3
            int k_min = -1;
            for(int d=3; d*d <= global_gcd; d++){
                if(global_gcd % d ==0){
                    k_min = d;
                    break;
                }
            }
            if(k_min == -1){
                // global_gcd is prime
                k_min = global_gcd;
            }
            printf("%d %d", global_gcd, k_min);
        }
    }
    free(level);
    return 0;
}