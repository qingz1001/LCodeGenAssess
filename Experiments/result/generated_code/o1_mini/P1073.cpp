#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges_fwd[MAXM];
Edge edges_rev[MAXM];
int head_fwd[MAXN], head_rev[MAXN];
int edge_cnt_fwd = 0, edge_cnt_rev = 0;

int n, m;
int y[MAXN];
int reachable1[MAXN];
int reachableN_[MAXN];
int stack_nodes[MAXN];
int stack_top = 0;
int scc_id[MAXN];
int current_scc = 0;
int min_y_scc[MAXN];
int in_deg[MAXN];
int *dag_adj[MAXN];
int dag_size[MAXN];
int queue[MAXN];
int front, rear;

void add_edge_fwd(int from, int to){
    edges_fwd[edge_cnt_fwd].to = to;
    edges_fwd[edge_cnt_fwd].next = head_fwd[from];
    head_fwd[from] = edge_cnt_fwd++;
}

void add_edge_rev(int from, int to){
    edges_rev[edge_cnt_rev].to = to;
    edges_rev[edge_cnt_rev].next = head_rev[from];
    head_rev[from] = edge_cnt_rev++;
}

int visited[MAXN];

// Iterative DFS for first pass
void dfs1(int u){
    int stack[MAXN];
    int top = 0;
    stack[top++] = u;
    while(top){
        int v = stack[top-1];
        if(!visited[v]){
            visited[v] = 1;
            for(int e = head_fwd[v]; e != -1; e = edges_fwd[e].next){
                int to = edges_fwd[e].to;
                if(!visited[to]){
                    stack[top++] = to;
                }
            }
        }
        else{
            stack_nodes[stack_top++] = v;
            top--;
        }
    }
}

// Iterative DFS for second pass
void dfs2(int u, int id){
    int stack[MAXN];
    int top = 0;
    stack[top++] = u;
    scc_id[u] = id;
    if(y[u] < min_y_scc[id]) min_y_scc[id] = y[u];
    while(top){
        int v = stack[top-1];
        int flag = 1;
        for(int e = head_rev[v]; e != -1; e = edges_rev[e].next){
            int to = edges_rev[e].to;
            if(reachable1[to] && reachableN_[to] && scc_id[to]==-1){
                scc_id[to] = id;
                if(y[to]<min_y_scc[id]) min_y_scc[id] = y[to];
                stack[top++] = to;
                flag = 0;
            }
        }
        if(flag){
            top--;
        }
    }
}

int main(){
    memset(head_fwd, -1, sizeof(head_fwd));
    memset(head_rev, -1, sizeof(head_rev));
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &y[i]);
    for(int i=0;i<m;i++){
        int x, y_, z;
        scanf("%d %d %d", &x, &y_, &z);
        add_edge_fwd(x, y_);
        add_edge_rev(y_, x);
        if(z == 2){
            add_edge_fwd(y_, x);
            add_edge_rev(x, y_);
        }
    }
    // BFS from 1
    memset(reachable1, 0, sizeof(reachable1));
    int *q = queue;
    front = rear = 0;
    q[rear++] = 1;
    reachable1[1] = 1;
    while(front < rear){
        int u = q[front++];
        for(int e = head_fwd[u]; e != -1; e = edges_fwd[e].next){
            int to = edges_fwd[e].to;
            if(!reachable1[to]){
                reachable1[to] = 1;
                q[rear++] = to;
            }
        }
    }
    // BFS from n on reverse graph
    memset(reachableN_, 0, sizeof(reachableN_));
    front = rear = 0;
    q[rear++] = n;
    reachableN_[n] = 1;
    while(front < rear){
        int u = q[front++];
        for(int e = head_rev[u]; e != -1; e = edges_rev[e].next){
            int to = edges_rev[e].to;
            if(!reachableN_[to]){
                reachableN_[to] = 1;
                q[rear++] = to;
            }
        }
    }
    // Kosaraju's algorithm
    memset(visited, 0, sizeof(visited));
    stack_top = 0;
    for(int i=1;i<=n;i++) {
        if(reachable1[i] && reachableN_[i] && !visited[i]){
            dfs1(i);
        }
    }
    // Second pass
    memset(scc_id, -1, sizeof(scc_id));
    for(int i=stack_top-1;i>=0;i--){
        int u = stack_nodes[i];
        if(scc_id[u]==-1){
            current_scc++;
            min_y_scc[current_scc] = y[u];
            dfs2(u, current_scc);
        }
    }
    // Build DAG
    for(int i=1;i<=current_scc;i++) {
        dag_adj[i] = NULL;
        dag_size[i] = 0;
        in_deg[i] = 0;
    }
    for(int u=1; u<=n; u++) {
        if(reachable1[u] && reachableN_[u]){
            for(int e = head_fwd[u]; e != -1; e = edges_fwd[e].next){
                int v = edges_fwd[e].to;
                if(reachable1[v] && reachableN_[v]){
                    if(scc_id[u] != scc_id[v]){
                        // Add edge from scc_id[u] to scc_id[v]
                        dag_size[scc_id[u]]++;
                        dag_adj[scc_id[u]] = realloc(dag_adj[scc_id[u]], dag_size[scc_id[u]] * sizeof(int));
                        dag_adj[scc_id[u]][dag_size[scc_id[u]]-1] = scc_id[v];
                        in_deg[scc_id[v]]++;
                    }
                }
            }
        }
    }
    // Topological sort
    int topo_order[current_scc];
    int topo_cnt = 0;
    front = rear = 0;
    for(int i=1;i<=current_scc;i++) if(in_deg[i]==0) queue[rear++] = i;
    while(front < rear){
        int u = queue[front++];
        topo_order[topo_cnt++] = u;
        for(int i=0;i<dag_size[u];i++){
            int v = dag_adj[u][i];
            in_deg[v]--;
            if(in_deg[v]==0){
                queue[rear++] = v;
            }
        }
    }
    // Propagate min_y
    for(int i=0;i<current_scc;i++) {
        int u = topo_order[i];
        if(dag_adj[u] != NULL){
            for(int j=0;j<dag_size[u];j++){
                int v = dag_adj[u][j];
                if(min_y_scc[v] > min_y_scc[u]){
                    min_y_scc[v] = min_y_scc[u];
                }
            }
        }
    }
    // Find max(y[j] - min_y[j])
    int result = 0;
    for(int u=1; u<=n; u++) {
        if(reachable1[u] && reachableN_[u]){
            int current_min = min_y_scc[scc_id[u]];
            if(y[u] - current_min > result){
                result = y[u] - current_min;
            }
        }
    }
    printf("%d\n", result > 0 ? result : 0);
    return 0;
}