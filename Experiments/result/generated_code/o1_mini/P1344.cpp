#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef long long ll;

typedef struct Edge {
    int to;
    ll cap;
    int rev;
} Edge;

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} AdjList;

#define MAXN 35
#define MAXM 2005

AdjList graph[MAXN];
int N, M;

void init_graph() {
    for(int i=1;i<=N;i++) {
        graph[i].edges = NULL;
        graph[i].size = 0;
        graph[i].capacity = 0;
    }
}

void add_edge(int from, int to, ll cap) {
    if(graph[from].size == graph[from].capacity){
        graph[from].capacity = graph[from].capacity ? graph[from].capacity *2 : 4;
        graph[from].edges = realloc(graph[from].edges, graph[from].capacity * sizeof(Edge));
    }
    graph[from].edges[graph[from].size].to = to;
    graph[from].edges[graph[from].size].cap = cap;
    graph[from].edges[graph[from].size].rev = graph[to].size;
    graph[from].size++;

    // Reverse edge
    if(graph[to].size == graph[to].capacity){
        graph[to].capacity = graph[to].capacity ? graph[to].capacity *2 : 4;
        graph[to].edges = realloc(graph[to].edges, graph[to].capacity * sizeof(Edge));
    }
    graph[to].edges[graph[to].size].to = from;
    graph[to].edges[graph[to].size].cap = 0;
    graph[to].edges[graph[to].size].rev = graph[from].size-1;
    graph[to].size++;
}

int level_graph[MAXN];
int ptr_graph[MAXN];

int bfs(int s, int t){
    memset(level_graph, -1, sizeof(level_graph));
    int queue[MAXN];
    int front=0, back=0;
    queue[back++] = s;
    level_graph[s] = 0;
    while(front < back){
        int u = queue[front++];
        for(int i=0;i<graph[u].size;i++){
            Edge e = graph[u].edges[i];
            if(e.cap >0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[u]+1;
                queue[back++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return level_graph[t] != -1;
}

ll dfs(int u, int t, ll flow){
    if(u == t) return flow;
    for(int *p = &ptr_graph[u]; *p < graph[u].size; (*p)++){
        Edge *e = &graph[u].edges[*p];
        if(e->cap >0 && level_graph[e->to] == level_graph[u]+1){
            ll pushed = dfs(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed >0){
                graph[u].edges[*p].cap -= pushed;
                graph[e->to].edges[e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t){
    ll flow = 0;
    while(bfs(s, t)){
        memset(ptr_graph, 0, sizeof(ptr_graph));
        while(1){
            ll pushed = dfs(s, t, 1e18);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d", &N, &M);
    init_graph();
    ll multiplier = M + 1;
    for(int i=0;i<M;i++){
        int S, E;
        ll C;
        scanf("%d %d %lld", &S, &E, &C);
        ll cap = C * multiplier + 1;
        add_edge(S, E, cap);
    }
    ll F = max_flow(1, N);
    ll C_total = F / multiplier;
    ll T = F % multiplier;
    printf("%lld %lld\n", C_total, T);
    // Free memory
    for(int i=1;i<=N;i++) {
        free(graph[i].edges);
    }
    return 0;
}