#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 3001
#define MAXR 8001
#define MAXP 3001
#define STACK_SIZE 3001

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
int n, p, r;

// Bribe cost, 0 means not bribable
int bribe[MAXN];

// Tarjan variables
int index_cnt = 0;
int indices[MAXN];
int lowlink[MAXN];
int onStack_flag[MAXN];
int stack_arr[STACK_SIZE];
int top = -1;
int scc_count = 0;
int node_to_scc[MAXN];
int scc_min_bribe[MAXN];
int scc_min_node[MAXN];
int scc_in_deg[MAXN];

void add_edge(int from, int to){
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

void tarjan_scc(int u){
    indices[u] = lowlink[u] = ++index_cnt;
    stack_arr[++top] = u;
    onStack_flag[u] = 1;
    Edge* e = graph[u];
    while(e){
        int v = e->to;
        if(indices[v]==0){
            tarjan_scc(v);
            if(lowlink[v]<lowlink[u]){
                lowlink[u] = lowlink[v];
            }
        }
        else if(onStack_flag[v]){
            if(indices[v]<lowlink[u]){
                lowlink[u] = indices[v];
            }
        }
        e = e->next;
    }
    if(lowlink[u]==indices[u]){
        scc_count++;
        int min_node = MAXN;
        int min_bribe = INT_MAX;
        while(1){
            int v = stack_arr[top--];
            onStack_flag[v] = 0;
            node_to_scc[v] = scc_count;
            if(v < min_node){
                min_node = v;
            }
            if(bribe[v] > 0 && bribe[v] < min_bribe){
                min_bribe = bribe[v];
            }
            if(v == u) break;
        }
        scc_min_node[scc_count] = min_node;
        if(min_bribe != INT_MAX){
            scc_min_bribe[scc_count] = min_bribe;
        }
        else{
            scc_min_bribe[scc_count] = -1;
        }
    }
}

int main(){
    // Initialize
    memset(graph, 0, sizeof(graph));
    memset(bribe, 0, sizeof(bribe));
    memset(indices, 0, sizeof(indices));
    memset(lowlink, 0, sizeof(lowlink));
    memset(onStack_flag, 0, sizeof(onStack_flag));
    memset(scc_min_bribe, -1, sizeof(scc_min_bribe));
    memset(scc_min_node, 0, sizeof(scc_min_node));
    memset(scc_in_deg, 0, sizeof(scc_in_deg));

    // Input
    scanf("%d", &n);
    scanf("%d", &p);
    for(int i=0;i<p;i++){
        int spy, cost;
        scanf("%d %d", &spy, &cost);
        if(bribe[spy]==0 || cost < bribe[spy]){
            bribe[spy] = cost;
        }
    }
    scanf("%d", &r);
    for(int i=0;i<r;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        add_edge(A, B);
    }

    // Tarjan's algorithm
    for(int u=1; u<=n; u++){
        if(indices[u]==0){
            tarjan_scc(u);
        }
    }

    // Build condensation graph and in-degrees
    for(int u=1; u<=n; u++){
        Edge* e = graph[u];
        while(e){
            int v = e->to;
            if(node_to_scc[u] != node_to_scc[v]){
                scc_in_deg[node_to_scc[v]]++;
            }
            e = e->next;
        }
    }

    // Find source SCCs
    int total_cost = 0;
    int impossible = 0;
    int min_uncontrolled = MAXN;
    for(int scc=1; scc<=scc_count; scc++){
        if(scc_in_deg[scc]==0){
            if(scc_min_bribe[scc]==-1){
                if(scc_min_node[scc] < min_uncontrolled){
                    min_uncontrolled = scc_min_node[scc];
                    impossible = 1;
                }
            }
            else{
                total_cost += scc_min_bribe[scc];
            }
        }
    }

    // Check if all SCCs are covered by sources
    if(impossible){
        printf("NO\n%d\n", min_uncontrolled);
    }
    else{
        // Now check if all nodes are reachable from the bribed sources
        // Since we have bribed all source SCCs, and the graph is condensed as DAG,
        // all nodes should be reachable. No need for extra checks.
        printf("YES\n%d\n", total_cost);
    }

    // Free memory
    for(int u=1; u<=n; u++){
        Edge* e = graph[u];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }

    return 0;
}