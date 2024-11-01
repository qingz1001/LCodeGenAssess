#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 20
#define MAX_TYPE3 10
#define MAX_OPERATIONS (2 * MAX_TASKS)
#define MAX_EDGES (MAX_OPERATIONS * MAX_OPERATIONS)

typedef struct {
    int type;
    int a;
    int b;
} Task;

typedef struct {
    int from;
    int to;
} Edge;

int main(){
    int n;
    Task tasks[MAX_TASKS];
    int type3_indices[MAX_TYPE3];
    int k = 0;
    
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d %d %d", &tasks[i].type, &tasks[i].a, &tasks[i].b);
        if(tasks[i].type == 3){
            type3_indices[k++] = i;
        }
    }
    
    int total_assignments = 1<<k;
    int min_makespan = 0x3f3f3f3f;
    
    for(int mask=0; mask<total_assignments; mask++){
        // Build dependencies
        int num_ops = 2*n;
        Edge edges[MAX_EDGES];
        int edge_count = 0;
        
        for(int i=0;i<n;i++){
            if(tasks[i].type ==1){
                edges[edge_count].from = 2*i;
                edges[edge_count].to = 2*i+1;
                edge_count++;
            }
            else if(tasks[i].type ==2){
                edges[edge_count].from = 2*i+1;
                edges[edge_count].to = 2*i;
                edge_count++;
            }
            else { // type3
                if( (mask & (1<< (type3_indices != NULL ? type3_indices[k>0?0:k] : 0))) ){
                    edges[edge_count].from = 2*i;
                    edges[edge_count].to = 2*i+1;
                }
                else{
                    edges[edge_count].from = 2*i+1;
                    edges[edge_count].to = 2*i;
                }
                edge_count++;
            }
        }
        
        // Initialize adjacency list and indegrees
        int adj[MAX_OPERATIONS][MAX_OPERATIONS];
        memset(adj, 0, sizeof(adj));
        int indegree[MAX_OPERATIONS];
        memset(indegree, 0, sizeof(indegree));
        for(int e=0;e<edge_count;e++){
            int from = edges[e].from;
            int to = edges[e].to;
            adj[from][to] = 1;
            indegree[to]++;
        }
        
        // Kahn's algorithm for topological sort
        int queue[MAX_OPERATIONS];
        int front=0, rear=0;
        for(int i=0;i<2*n;i++) if(indegree[i]==0) queue[rear++] = i;
        
        int topo_order[MAX_OPERATIONS];
        int idx =0;
        while(front < rear){
            int u = queue[front++];
            topo_order[idx++] = u;
            for(int v=0; v<2*n; v++) {
                if(adj[u][v]){
                    indegree[v]--;
                    if(indegree[v]==0){
                        queue[rear++] = v;
                    }
                }
            }
        }
        
        if(idx != 2*n){
            continue; // cycle detected, invalid assignment
        }
        
        // Schedule operations
        int earliest_start[MAX_OPERATIONS];
        memset(earliest_start, 0, sizeof(earliest_start));
        int machine_A =0, machine_B=0;
        for(int i=0;i<idx;i++){
            int op = topo_order[i];
            int machine = (op %2 ==0)? 0:1; // 0 for A, 1 for B
            int duration = (op %2 ==0)? tasks[op/2].a : tasks[op/2].b;
            int est = 0;
            // Find max finish time of predecessors
            for(int u=0; u<2*n; u++) {
                if(adj[u][op]){
                    // Not possible as we have already processed dependencies
                }
            }
            // To find predecessors, iterate edges
            for(int e=0; e<edge_count; e++){
                if(edges[e].to == op){
                    if(edges[e].from != -1){
                        if(earliest_start[edges[e].from] + ((edges[e].from %2 ==0)? tasks[edges[e].from/2].a : tasks[edges[e].from/2].b) > est){
                            est = earliest_start[edges[e].from] + ((edges[e].from %2 ==0)? tasks[edges[e].from/2].a : tasks[edges[e].from/2].b);
                        }
                    }
                }
            }
            if(machine ==0){
                if(machine_A > est){
                    est = machine_A;
                }
                machine_A = est + duration;
            }
            else{
                if(machine_B > est){
                    est = machine_B;
                }
                machine_B = est + duration;
            }
            earliest_start[op] = est;
        }
        
        int makespan = (machine_A > machine_B)? machine_A : machine_B;
        if(makespan < min_makespan){
            min_makespan = makespan;
        }
    }
    
    printf("%d\n", min_makespan);
    return 0;
}