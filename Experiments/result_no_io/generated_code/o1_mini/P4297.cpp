#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1026
#define MAXE 2000000
#define INF 100000000000LL

typedef long long ll;

struct Edge {
    int to;
    ll cap;
    int next;
} edges[MAXE];
int head_nodes[MAXN];
int edge_ptr = 0;

void add_edge(int from, int to, ll cap){
    edges[edge_ptr].to = to;
    edges[edge_ptr].cap = cap;
    edges[edge_ptr].next = head_nodes[from];
    head_nodes[from] = edge_ptr;
    edge_ptr++;

    edges[edge_ptr].to = from;
    edges[edge_ptr].cap = 0;
    edges[edge_ptr].next = head_nodes[to];
    head_nodes[to] = edge_ptr;
    edge_ptr++;
}

int level_graph[MAXN];
int ptr_ptr[MAXN];
int queue_nodes[MAXN];

void bfs(int s, int t){
    memset(level_graph, -1, sizeof(level_graph));
    int front = 0, back = 0;
    queue_nodes[back++] = s;
    level_graph[s] = 0;
    while(front < back){
        int u = queue_nodes[front++];
        for(int e = head_nodes[u]; e != -1; e = edges[e].next){
            if(edges[e].cap > 0 && level_graph[edges[e].to] == -1){
                level_graph[edges[e].to] = level_graph[u] + 1;
                queue_nodes[back++] = edges[e].to;
                if(edges[e].to == t){
                    break;
                }
            }
        }
    }
}

ll dfs(int u, int t, ll flow){
    if(u == t) return flow;
    for(int *e = &ptr_ptr[u]; *e != -1; e = &ptr_ptr[u]){
        int edge = *e;
        if(edges[edge].cap > 0 && level_graph[edges[edge].to] == level_graph[u] + 1){
            ll pushed = dfs(edges[edge].to, t, (flow < edges[edge].cap) ? flow : edges[edge].cap);
            if(pushed > 0){
                edges[edge].cap -= pushed;
                edges[edge^1].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t){
    ll flow = 0;
    while(1){
        bfs(s, t);
        if(level_graph[t] == -1) break;
        memset(ptr_ptr, -1, sizeof(ptr_ptr));
        while(1){
            ll pushed = dfs(s, t, INF);
            if(pushed == 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    memset(head_nodes, -1, sizeof(head_nodes));
    int N;
    scanf("%d", &N);
    int M = 1 << N;
    int init[M+1];
    for(int i =1;i<=M;i++) scanf("%d", &init[i]);
    ll C[M+1];
    for(int i=1;i<=M;i++) scanf("%lld", &C[i]);
    // Read F and add edges
    for(int i=1;i<M;i++){
        for(int j=1; j<=M-i; j++){
            ll F;
            scanf("%lld", &F);
            add_edge(i, i+j, F);
        }
    }
    int source = 0;
    int sink = M+1;
    // Connect users to source or sink
    for(int i=1;i<=M;i++){
        if(init[i]==0){
            add_edge(i, sink, C[i]);
        }
        else{
            add_edge(source, i, C[i]);
        }
    }
    ll result = max_flow(source, sink);
    printf("%lld\n", result);
    return 0;
}