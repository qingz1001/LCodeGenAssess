#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct Edge {
    int to;
    int w;
    struct Edge* next;
} Edge;

int n, m;
Edge** adj;
ll w_sum = 0;
ll* size_sub;
int parent_node;

// Function to add edge
void add_edge(int u, int v, int w){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->w = w;
    edge->next = adj[u];
    adj[u] = edge;
}

ll dfs(int u, int parent){
    size_sub[u] = 1;
    Edge* edge = adj[u];
    while(edge){
        int v = edge->to;
        if(v != parent){
            size_sub[u] += dfs(v, u);
        }
        edge = edge->next;
    }
    return size_sub[u];
}

int main(){
    scanf("%d %d", &n, &m);
    adj = (Edge**)calloc(n+1, sizeof(Edge*));
    size_sub = (ll*)calloc(n+1, sizeof(ll));
    int u, v, w;
    // To handle multiple edges in case of cycle
    // We assume the graph is connected and has at most one cycle
    // So we can consider it as a tree and possibly one extra edge
    // First, build the adjacency list
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // Perform DFS from node 1
    dfs(1, -1);
    // Now, calculate the expected length
    double E = 0.0;
    // Iterate through all edges once
    // To avoid double counting, we need to traverse edges in one direction
    // We perform another DFS to accumulate the contributions
    // Reset visited
    int* visited = (int*)calloc(n+1, sizeof(int));
    // Stack for DFS
    typedef struct StackNode {
        int u;
        int parent;
        struct StackNode* next;
    } StackNode;
    StackNode* stack = NULL;
    // Push root
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->u = 1;
    new_node->parent = -1;
    new_node->next = stack;
    stack = new_node;
    while(stack){
        int current = stack->u;
        int parent = stack->parent;
        stack = stack->next;
        if(visited[current]) continue;
        visited[current] = 1;
        Edge* edge = adj[current];
        while(edge){
            int v = edge->to;
            if(v != parent){
                // To ensure each edge is counted once
                if(parent == -1 || v > parent){
                    ll a = size_sub[v];
                    ll b = n - a;
                    E += (double)(edge->w) * 2.0 * a * b / ((double)n * n);
                }
                stack = (StackNode*)malloc(sizeof(StackNode));
                stack->u = v;
                stack->parent = current;
                stack->next = stack;
            }
            edge = edge->next;
        }
    }
    printf("%.5lf\n", E);
    return 0;
}