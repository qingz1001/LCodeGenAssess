#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1024
#define MAXE 2000000
#define INF 1000000000

typedef struct Edge {
    int to;
    int rev;
    long long cap;
} Edge;

Edge edges[MAXE];
int head[MAXN + 2];
int ptr_edge = 0;

void add_edge(int from, int to, long long cap){
    edges[ptr_edge].to = to;
    edges[ptr_edge].cap = cap;
    edges[ptr_edge].rev = ptr_edge + 1;
    head[from]++;
    ptr_edge++;

    edges[ptr_edge].to = from;
    edges[ptr_edge].cap = 0;
    edges[ptr_edge].rev = ptr_edge -1;
    head[to]++;
    ptr_edge++;
}

int level_graph[MAXN +2];
int ptr[MAXN +2];
int q[MAXN * 2];

int bfs(int s, int t){
    memset(level_graph, -1, sizeof(int)*(MAXN+2));
    int front =0, rear=0;
    q[rear++] = s;
    level_graph[s]=0;
    while(front < rear){
        int u = q[front++];
        for(int i=0; i<head[u]; i++){
            Edge e = edges[u*MAXN +i];
            if(e.cap >0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[u] +1;
                q[rear++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return 0;
}

long long dfs(int u, int t, long long flow){
    if(u == t) return flow;
    for(int i=ptr[u]; i<head[u]; i++){
        Edge *e = &edges[u*MAXN +i];
        if(e->cap >0 && level_graph[e->to] == level_graph[u] +1){
            long long pushed = dfs(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed >0){
                edges[u*MAXN +i].cap -= pushed;
                edges[e->to*MAXN +e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

long long max_flow_func(int s, int t){
    long long flow =0;
    while(bfs(s, t)){
        memset(ptr, 0, sizeof(int)*(MAXN+2));
        while(1){
            long long pushed = dfs(s, t, INF);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int N;
    scanf("%d", &N);
    int M = 1<<N;
    int mode[M+1];
    for(int i=1;i<=M;i++) scanf("%d", &mode[i]);
    long long C[M+1];
    for(int i=1;i<=M;i++) scanf("%lld", &C[i]);
    long long F[M+1][M+1];
    memset(F, 0, sizeof(F));
    for(int i=1;i<M;i++){
        for(int j= i+1; j<=M; j++) {
            scanf("%lld", &F[i][j]);
            F[j][i] = F[i][j];
        }
    }
    // Reset head
    memset(head, 0, sizeof(head));
    // Add edges
    int s = 0, t_node = M+1;
    for(int i=1;i<=M;i++){
        if(mode[i]==0){
            // Initially A, connect to sink with C_i
            add_edge(i, t_node, C[i]);
        }
        else{
            // Initially B, connect source to i with C_i
            add_edge(s, i, C[i]);
        }
    }
    // Add F_{i,j} edges
    for(int i=1;i<=M;i++){
        for(int j=i+1;j<=M;j++){
            if(F[i][j]>0){
                add_edge(i, j, F[i][j]);
                add_edge(j, i, F[i][j]);
            }
        }
    }
    long long res = max_flow_func(s, t_node);
    printf("%lld\n", res);
    return 0;
}