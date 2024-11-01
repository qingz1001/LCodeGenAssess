#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXB 25
#define MAXV (MAXN + MAXB + 2)
#define INF 1000000000

typedef struct Edge {
    int to, rev;
    int cap;
} Edge;

Edge graph[MAXV][MAXV];
int graph_ptr[MAXV];
int level_graph[MAXV];
int ptr_graph[MAXV];
int V;

void add_edge(int from, int to, int cap){
    graph[from][graph_ptr[from]].to = to;
    graph[from][graph_ptr[from]].cap = cap;
    graph[from][graph_ptr[from]].rev = graph_ptr[to];
    graph[to][graph_ptr[to]].to = from;
    graph[to][graph_ptr[to]].cap = 0;
    graph[to][graph_ptr[to]].rev = graph_ptr[from];
    graph_ptr[from]++;
    graph_ptr[to]++;
}

int bfs(int s, int t){
    memset(level_graph, -1, sizeof(int)*(V+1));
    int q[MAXV], front=0, back=0;
    q[back++] = s;
    level_graph[s] = 0;
    while(front < back){
        int u = q[front++];
        for(int i=0;i<graph_ptr[u];i++){
            Edge e = graph[u][i];
            if(e.cap > 0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[u]+1;
                q[back++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *p=&ptr_graph[u]; *p < graph_ptr[u]; (*p)++){
        Edge e = graph[u][*p];
        if(e.cap > 0 && level_graph[e.to] == level_graph[u]+1){
            int pushed = dfs(e.to, t, flow < e.cap ? flow : e.cap);
            if(pushed > 0){
                graph[u][*p].cap -= pushed;
                graph[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow=0;
    while(bfs(s, t)){
        memset(ptr_graph, 0, sizeof(int)*(V+1));
        while(1){
            int pushed = dfs(s, t, INF);
            if(pushed <= 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int N, B;
    scanf("%d %d", &N, &B);
    int prefs[N][B];
    for(int i=0;i<N;i++) {
        for(int j=0;j<B;j++) {
            scanf("%d", &prefs[i][j]);
            prefs[i][j]--; // zero-based
        }
    }
    int cap[B];
    for(int i=0;i<B;i++) scanf("%d", &cap[i]);
    int min_range = B, result = B;
    for(int low=0; low<B; low++){
        for(int high=low; high<B; high++){
            if(high - low +1 >= result) continue;
            // Build flow network
            V = N + B + 2;
            memset(graph_ptr, 0, sizeof(int)*(V+1));
            int S = N + B;
            int T = N + B +1;
            for(int i=0;i<N;i++){
                add_edge(S, i, 1);
                for(int j=low; j<=high && j<B; j++){
                    add_edge(i, N + prefs[i][j], 1);
                }
            }
            for(int i=0;i<B;i++) add_edge(N + i, T, cap[i]);
            if(max_flow(S, T) == N){
                result = high - low +1;
                break;
            }
        }
    }
    printf("%d\n", result);
}