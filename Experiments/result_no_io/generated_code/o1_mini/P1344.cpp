#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int to;
    long long capacity;
    int rev;
} Edge;

int N, M;
Edge* adj[33];
int adj_size[33];
int adj_cap[33];

void add_edge(int from, int to, long long cap) {
    Edge forward = {to, cap, adj_size[to]};
    Edge backward = {from, 0, adj_size[from]};
    adj[from] = realloc(adj[from], sizeof(Edge) * (adj_size[from] + 1));
    adj[from][adj_size[from]] = forward;
    adj_size[from]++;
    
    adj[to] = realloc(adj[to], sizeof(Edge) * (adj_size[to] + 1));
    adj[to][adj_size[to]] = backward;
    adj_size[to]++;
}

int level[33];
int ptr_idx[33];

int bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    int queue[33], front=0, back=0;
    queue[back++] = s;
    level[s] = 0;
    while(front < back){
        int u = queue[front++];
        for(int i=0;i<adj_size[u];i++){
            Edge e = adj[u][i];
            if(e.capacity > 0 && level[e.to]==-1){
                level[e.to] = level[u] + 1;
                queue[back++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return 0;
}

long long dfs(int u, int t, long long flow) {
    if(u == t) return flow;
    for(int *p = &ptr_idx[u]; *p < adj_size[u]; (*p)++) {
        Edge *e = &adj[u][*p];
        if(e->capacity > 0 && level[e->to] == level[u] + 1){
            long long pushed = dfs(e->to, t, flow < e->capacity ? flow : e->capacity);
            if(pushed > 0){
                adj[u][*p].capacity -= pushed;
                adj[e->to][e->rev].capacity += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

long long max_flow(int s, int t){
    long long flow = 0;
    while(bfs(s, t)){
        memset(ptr_idx, 0, sizeof(ptr_idx));
        while(1){
            long long pushed = dfs(s, t, 1e18);
            if(pushed == 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++){
        int S, E;
        long long C;
        scanf("%d %d %lld", &S, &E, &C);
        add_edge(S, E, C * (M+1) + 1);
    }
    long long flow = max_flow(1, N);
    long long C = flow / (M+1);
    long long T = flow % (M+1);
    printf("%lld %lld\n", C, T);
    for(int i=1;i<=N;i++) {
        free(adj[i]);
    }
    return 0;
}