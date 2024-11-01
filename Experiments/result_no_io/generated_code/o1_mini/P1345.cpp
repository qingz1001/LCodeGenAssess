#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define INF 1000000

struct Edge {
    int to;
    int rev;
    int cap;
} graph[MAXN][MAXN];
int graph_size[MAXN];

void add_edge(int from, int to, int cap){
    graph[from][graph_size[from]].to = to;
    graph[from][graph_size[from]].cap = cap;
    graph[from][graph_size[from]].rev = graph_size[to];
    graph_size[from]++;
    
    graph[to][graph_size[to]].to = from;
    graph[to][graph_size[to]].cap = 0;
    graph[to][graph_size[to]].rev = graph_size[from]-1;
    graph_size[to]++;
}

int level_nodes[MAXN];
int ptr_nodes[MAXN];

int bfs(int s, int t){
    memset(level_nodes, -1, sizeof(level_nodes));
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = s;
    level_nodes[s] = 0;
    while(front < rear){
        int u = queue[front++];
        for(int i=0;i<graph_size[u];i++){
            struct Edge e = graph[u][i];
            if(e.cap > 0 && level_nodes[e.to]==-1){
                level_nodes[e.to] = level_nodes[u] + 1;
                queue[rear++] = e.to;
                if(e.to == t) break;
            }
        }
    }
    return level_nodes[t] != -1;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *i=&ptr_nodes[u]; *i < graph_size[u]; (*i)++){
        struct Edge e = graph[u][*i];
        if(e.cap > 0 && level_nodes[e.to] == level_nodes[u]+1){
            int pushed = dfs(e.to, t, flow < e.cap ? flow : e.cap);
            if(pushed > 0){
                graph[u][*i].cap -= pushed;
                graph[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int dinic(int s, int t){
    int flow = 0;
    while(bfs(s, t)){
        memset(ptr_nodes, 0, sizeof(ptr_nodes));
        while(1){
            int pushed = dfs(s, t, INF);
            if(pushed == 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int N,M,c1,c2;
    scanf("%d %d %d %d", &N, &M, &c1, &c2);
    // Assign node indices
    // Nodes 1..N: in nodes
    // Nodes N+1..2N: out nodes
    // c1 and c2 are not split
    for(int u=1; u<=N; u++){
        if(u != c1 && u != c2){
            add_edge(u, u + N, 1);
        }
    }
    for(int i=0; i<M; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        // Connect u to v
        if(u != c1 && u != c2){
            u = u + N;
        }
        if(v != c1 && v != c2){
            v = v;
        }
        add_edge(u, v, INF);
        // Connect v to u
        if(v != c1 && v != c2){
            v = v + N;
        }
        if(u != c1 && u != c2){
            u = u - N;
        }
        add_edge(v, u, INF);
    }
    int s = c1;
    int t = c2;
    printf("%d\n", dinic(s, t));
    return 0;
}