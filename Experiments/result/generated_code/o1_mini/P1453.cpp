#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    int to;
    int next;
} Edge;

typedef struct {
    int node;
    int parent;
    int state; // 0: first visit, 1: processing children
} StackFrame;

typedef struct {
    int node;
    int parent;
} CycleStackFrame;

int main(){
    int n;
    scanf("%d", &n);
    int *p = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &p[i]);
    int max_edges = 2*n;
    Edge *edges = (Edge*)malloc(max_edges * sizeof(Edge));
    int *head = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) head[i]=-1;
    int m=0;
    for(int i=0;i<n;i++){
        int u,v;
        scanf("%d %d", &u, &v);
        edges[m].to = v;
        edges[m].next = head[u];
        head[u] = m++;
        edges[m].to = u;
        edges[m].next = head[v];
        head[v] = m++;
    }
    double k;
    scanf("%lf", &k);
    // Find cycle
    int *visited = (int*)calloc(n, sizeof(int));
    int *parent_dfs = (int*)malloc(n * sizeof(int));
    memset(parent_dfs, -1, n * sizeof(int));
    int cycle_start = -1, cycle_end = -1;
    int stack_ptr = 0;
    int *stack_nodes = (int*)malloc(n * sizeof(int));
    // Iterative DFS to find cycle
    StackFrame *dfs_stack = (StackFrame*)malloc((n+1) * sizeof(StackFrame));
    int dfs_top = 0;
    dfs_stack[dfs_top].node = 0;
    dfs_stack[dfs_top].parent = -1;
    dfs_stack[dfs_top].state = 0;
    dfs_top++;
    while(dfs_top > 0){
        dfs_top--;
        StackFrame current = dfs_stack[dfs_top];
        int u = current.node;
        if(current.state == 0){
            if(visited[u]){
                continue;
            }
            visited[u] = 1;
            // Push back with state=1 to handle after children
            dfs_stack[dfs_top].node = u;
            dfs_stack[dfs_top].parent = current.parent;
            dfs_stack[dfs_top].state = 1;
            dfs_top++;
            // Iterate neighbors
            for(int e = head[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(v == current.parent) continue;
                if(!visited[v]){
                    parent_dfs[v] = u;
                    dfs_stack[dfs_top].node = v;
                    dfs_stack[dfs_top].parent = u;
                    dfs_stack[dfs_top].state = 0;
                    dfs_top++;
                }
                else{
                    // Found cycle
                    cycle_start = v;
                    cycle_end = u;
                    break;
                }
            }
            if(cycle_start != -1){
                break;
            }
        }
    }
    // Collect cycle nodes
    int cycle_len = 0;
    int *in_cycle = (int*)calloc(n, sizeof(int));
    if(cycle_start != -1){
        cycle_len = 1;
        in_cycle[cycle_end] = 1;
        int x = cycle_end;
        while(x != cycle_start){
            x = parent_dfs[x];
            in_cycle[x] = 1;
            cycle_len++;
        }
    }
    // Collect cycle in order
    int *cycle = (int*)malloc(cycle_len * sizeof(int));
    int idx = 0;
    int x = cycle_start;
    cycle[idx++] = x;
    while(x != cycle_end){
        x = parent_dfs[x];
        cycle[idx++] = x;
    }
    // Now, prepare for tree DP
    // Remove cycle edges
    int *is_cycle_edge = (int*)calloc(2*m, sizeof(int));
    for(int i=0;i<cycle_len;i++){
        int u = cycle[i];
        int v = cycle[(i+1)%cycle_len];
        // Mark both directions
        for(int e = head[u]; e != -1; e = edges[e].next){
            if(edges[e].to == v){
                is_cycle_edge[e] = 1;
                break;
            }
        }
        for(int e = head[v]; e != -1; e = edges[e].next){
            if(edges[e].to == u){
                is_cycle_edge[e] = 1;
                break;
            }
        }
    }
    // Now, build adjacency list without cycle edges
    // Prepare for tree DP
    // For each cycle node, collect their tree neighbors
    int **tree_adj = (int**)malloc(n * sizeof(int*));
    int *tree_size = (int*)calloc(n, sizeof(int));
    for(int e=0;e<2*m;e++) {
        if(is_cycle_edge[e]) continue;
        int u = -1, v = -1;
        // Find u from edge index
        // This is tricky, but since we have no reverse mapping, skip
        // Instead, later process trees
    }
    // Instead of modifying, we'll process trees separately
    // Implement tree DP
    // To store MTE_sum and MTS_sum for cycle nodes
    ll *MTE_sum = (ll*)calloc(n, sizeof(ll));
    ll *MTS_sum = (ll*)calloc(n, sizeof(ll));
    // To mark cycle nodes
    // Already have in_cycle array
    // Iterate over cycle nodes and process their trees
    // Implement iterative DFS for trees
    // Prepare adjacency list without cycle edges
    // Rebuild adjacency list without cycle edges
    int *tree_head = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) tree_head[i] = -1;
    int tree_m = 0;
    for(int e=0;e<2*m;e++){
        int u = -1, v = -1;
        // To find u and v, we need to iterate again
        // Reconstruct u from e
        // Not stored, so alternative approach:
        // Reconstruct all edges with u < v and map
        // Alternatively, skip and reprocess
    }
    // Instead, process trees by traversing from cycle nodes
    // Implement visited for trees
    int *visited_tree = (int*)calloc(n, sizeof(int));
    for(int i=0;i<cycle_len;i++){
        int u = cycle[i];
        // Iterate neighbors
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(in_cycle[v] || v == cycle[(i-1+cycle_len)%cycle_len] || v == cycle[(i+1)%cycle_len]) continue;
            if(visited_tree[v]) continue;
            // Now, v is root of a tree
            // Perform iterative DFS
            StackFrame *stack = (StackFrame*)malloc(n * sizeof(StackFrame));
            int top = 0;
            stack[top].node = v;
            stack[top].parent = u;
            stack[top].state = 0;
            top++;
            // To store include and exclude
            ll *include = (ll*)malloc(n * sizeof(ll));
            ll *exclude = (ll*)malloc(n * sizeof(ll));
            // Initialize
            while(top > 0){
                StackFrame current = stack[top-1];
                if(current.state == 0){
                    stack[top-1].state = 1;
                    // Push children
                    for(int ee = head[current.node]; ee != -1; ee = edges[ee].next){
                        int nei = edges[ee].to;
                        if(nei == current.parent || in_cycle[nei]) continue;
                        if(!visited_tree[nei]){
                            stack[top].node = nei;
                            stack[top].parent = current.node;
                            stack[top].state = 0;
                            top++;
                        }
                    }
                }
                else{
                    top--;
                    // Compute include and exclude
                    ll inc = p[current.node];
                    ll exc = 0;
                    for(int ee = head[current.node]; ee != -1; ee = edges[ee].next){
                        int nei = edges[ee].to;
                        if(nei == current.parent || in_cycle[nei]) continue;
                        if(!visited_tree[nei]){
                            inc += exclude[nei];
                            exc += (include[nei] > exclude[nei] ? include[nei] : exclude[nei]);
                        }
                    }
                    include[current.node] = inc;
                    exclude[current.node] = exc;
                    if(current.parent == u){
                        MTE_sum[u] += exclude[current.node];
                        ll temp = (include[current.node] > exclude[current.node] ? include[current.node] : exclude[current.node]);
                        MTS_sum[u] += temp;
                    }
                    visited_tree[current.node] = 1;
                }
            }
            free(include);
            free(exclude);
            free(stack);
        }
    }
    // Now, prepare cycle node values
    ll *v_val = (ll*)malloc(cycle_len * sizeof(ll));
    ll *w_val = (ll*)malloc(cycle_len * sizeof(ll));
    for(int i=0;i<cycle_len;i++){
        int u = cycle[i];
        v_val[i] = (ll)p[u] + MTE_sum[u];
        w_val[i] = MTS_sum[u];
    }
    // Case 1: first included, last excluded
    ll prev0 = LLONG_MIN/2;
    ll prev1 = v_val[0];
    for(int i=1;i<cycle_len;i++){
        ll temp0 = (prev0 > prev1 ? prev0 : prev1) + w_val[i];
        ll temp1 = prev0 + v_val[i];
        prev0 = temp0;
        prev1 = temp1;
    }
    ll case1 = prev0;
    // Case 2: first excluded
    prev0 = w_val[0];
    prev1 = LLONG_MIN/2;
    for(int i=1;i<cycle_len;i++){
        ll temp0 = (prev0 > prev1 ? prev0 : prev1) + w_val[i];
        ll temp1 = prev0 + v_val[i];
        prev0 = temp0;
        prev1 = temp1;
    }
    ll case2 = (prev0 > prev1 ? prev0 : prev1);
    ll total = (case1 > case2 ? case1 : case2);
    // Now, multiply by k
    double result = (double)total * k;
    // Print with one decimal
    printf("%.1lf\n", result);
    // Free memory
    free(p);
    free(edges);
    free(head);
    free(visited);
    free(parent_dfs);
    free(stack_nodes);
    free(dfs_stack);
    free(in_cycle);
    free(cycle);
    free(MTE_sum);
    free(MTS_sum);
    free(tree_head);
    free(visited_tree);
    free(v_val);
    free(w_val);
    return 0;
}