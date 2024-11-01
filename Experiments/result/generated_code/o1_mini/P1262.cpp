#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 3001
#define MAX_R 8001

// Adjacency list using head and next_edge
int head_adj[MAX_N];
int to_node[MAX_R];
int next_edge[MAX_R];
int edge_count = 0;

// Tarjan's variables
int indices_tarjan[MAX_N];
int lowlink[MAX_N];
int on_stack_tarjan[MAX_N];
int stack_tarjan[MAX_N];
int stack_top = -1;
int component_ids[MAX_N];
int component_count = 0;

// For components
int min_bribe[3001];
int min_node_component[3001];
int in_degree[3001];

// Bribe costs
int bribe_cost[MAX_N];

// Function to push to stack
void push_stack(int u) {
    stack_tarjan[++stack_top] = u;
    on_stack_tarjan[u] = 1;
}

// Function to pop from stack
int pop_stack() {
    int u = stack_tarjan[stack_top--];
    on_stack_tarjan[u] = 0;
    return u;
}

// Tarjan's algorithm
void tarjan(int u) {
    static int index_counter = 0;
    indices_tarjan[u] = lowlink[u] = ++index_counter;
    push_stack(u);
    // Traverse all neighbors
    for(int e = head_adj[u]; e != -1; e = next_edge[e]) {
        int v = to_node[e];
        if(indices_tarjan[v] == 0) {
            tarjan(v);
            if(lowlink[v] < lowlink[u])
                lowlink[u] = lowlink[v];
        }
        else if(on_stack_tarjan[v]) {
            if(indices_tarjan[v] < lowlink[u])
                lowlink[u] = indices_tarjan[v];
        }
    }
    // If u is a root node, pop the stack and generate a component
    if(lowlink[u] == indices_tarjan[u]) {
        component_count++;
        min_node_component[component_count] = INT_MAX;
        min_bribe[component_count] = INT_MAX;
        while(1) {
            int w = pop_stack();
            component_ids[w] = component_count;
            if(w < min_node_component[component_count])
                min_node_component[component_count] = w;
            if(bribe_cost[w] != -1 && bribe_cost[w] < min_bribe[component_count])
                min_bribe[component_count] = bribe_cost[w];
            if(w == u)
                break;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    
    // Initialize
    for(int i=1;i<=n;i++) {
        head_adj[i] = -1;
        bribe_cost[i] = -1;
    }
    
    int p;
    scanf("%d", &p);
    for(int i=0;i<p;i++){
        int spy, cost;
        scanf("%d %d", &spy, &cost);
        if(bribe_cost[spy]==-1 || cost < bribe_cost[spy])
            bribe_cost[spy] = cost;
    }
    
    int r;
    scanf("%d", &r);
    for(int i=0;i<r;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        to_node[edge_count] = B;
        next_edge[edge_count] = head_adj[A];
        head_adj[A] = edge_count++;
    }
    
    // Run Tarjan's algorithm
    for(int u=1; u<=n; u++) {
        if(indices_tarjan[u]==0){
            tarjan(u);
        }
    }
    
    // Initialize in_degree
    for(int c=1; c<=component_count; c++)
        in_degree[c] = 0;
    
    // Build in_degree for components
    for(int u=1; u<=n; u++) {
        for(int e = head_adj[u]; e != -1; e = next_edge[e]) {
            int v = to_node[e];
            if(component_ids[u] != component_ids[v]){
                in_degree[component_ids[v]]++;
            }
        }
    }
    
    // Initialize min_node_component and min_bribe already done in Tarjan
    // Now find source components
    long long total_cost = 0;
    int min_uncontrolled = n+1;
    for(int c=1; c<=component_count; c++) {
        if(in_degree[c]==0){
            if(min_bribe[c] != INT_MAX){
                total_cost += min_bribe[c];
            }
            else{
                if(min_node_component[c] < min_uncontrolled)
                    min_uncontrolled = min_node_component[c];
            }
        }
    }
    
    if(min_uncontrolled > n){
        printf("YES\n%lld\n", total_cost);
    }
    else{
        printf("NO\n%d\n", min_uncontrolled);
    }
    
    return 0;
}