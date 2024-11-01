#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 300005

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

Edge *graph[MAXN], *rev_graph[MAXN];
int order[MAXN], scc_id[MAXN];
int stack_nodes[MAXN], top = 0;
int n, m;
int current_order = 0;
int current_scc = 0;
int scc_size[MAXN];
int scc_count;
Edge *scc_graph[MAXN];
long long reach[MAXN];
int in_deg[MAXN];

// Function to add edge to adjacency list
void add_edge(Edge *graph[], int from, int to){
    Edge *new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

// Iterative DFS for first pass
void dfs1(int u){
    int stack[MAXN];
    int top_stack = 0;
    stack[top_stack++] = u;
    int visited[MAXN] = {0};
    while(top_stack > 0){
        int node = stack[top_stack-1];
        if(!visited[node]){
            visited[node] = 1;
            for(Edge *e = graph[node]; e != NULL; e = e->next){
                if(!visited[e->to]){
                    stack[top_stack++] = e->to;
                }
            }
        } else {
            stack_nodes[top++] = node;
            top_stack--;
        }
    }
}

// Iterative DFS for second pass
void dfs2(int u, int label){
    int stack_iter[MAXN];
    int top_iter = 0;
    stack_iter[top_iter++] = u;
    scc_id[u] = label;
    while(top_iter > 0){
        int node = stack_iter[top_iter-1];
        stack_iter[top_iter-1] = -1; // Mark as processed
        for(Edge *e = rev_graph[node]; e != NULL; e = e->next){
            if(scc_id[e->to] == -1){
                scc_id[e->to] = label;
                stack_iter[top_iter++] = e->to;
            }
        }
        top_iter--;
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(graph, u, v);
        add_edge(rev_graph, v, u);
    }

    // First pass
    for(int i=1;i<=n;i++){
        if(scc_id[i] == 0){
            dfs1(i);
        }
    }

    // Initialize scc_id to -1
    memset(scc_id, -1, sizeof(scc_id));

    // Second pass
    for(int i=top-1;i>=0;i--){
        int node = stack_nodes[i];
        if(scc_id[node] == -1){
            dfs2(node, current_scc);
            current_scc++;
        }
    }
    scc_count = current_scc;

    // Count size of each SCC
    for(int i=1;i<=n;i++) {
        scc_size[scc_id[i]]++;
    }

    // Build condensation graph
    for(int u=1;u<=n;u++){
        for(Edge *e = graph[u]; e != NULL; e = e->next){
            int su = scc_id[u];
            int sv = scc_id[e->to];
            if(su != sv){
                add_edge(scc_graph, su, sv);
                in_deg[sv]++;
            }
        }
    }

    // Topological sort using Kahn's algorithm
    int queue[MAXN];
    int front = 0, rear = 0;
    for(int i=0;i<scc_count;i++){
        if(in_deg[i] == 0){
            queue[rear++] = i;
        }
    }

    // Initialize reach counts
    for(int i=0;i<scc_count;i++){
        reach[i] = scc_size[i];
    }

    while(front < rear){
        int u = queue[front++];
        for(Edge *e = scc_graph[u]; e != NULL; e = e->next){
            reach[e->to] += reach[u];
            in_deg[e->to]--;
            if(in_deg[e->to] == 0){
                queue[rear++] = e->to;
            }
        }
    }

    // Assign reach counts to nodes
    long long result[MAXN];
    for(int i=1;i<=n;i++){
        result[i] = reach[scc_id[i]];
    }

    // Print the results
    for(int i=1;i<=n;i++){
        printf("%lld ", result[i]);
    }
    return 0;
}