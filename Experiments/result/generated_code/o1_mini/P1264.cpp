#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 700
#define INF 100000000

typedef struct Edge {
    int to, rev;
    int cap;
} Edge;

Edge graph[MAXN][MAXN];
int graph_size[MAXN];
int level_graph[MAXN];
int ptr_graph[MAXN];
int total_nodes;

void add_edge(int from, int to, int cap) {
    graph[from][graph_size[from]].to = to;
    graph[from][graph_size[from]].cap = cap;
    graph[from][graph_size[from]].rev = graph_size[to];
    graph_size[from]++;
    
    graph[to][graph_size[to]].to = from;
    graph[to][graph_size[to]].cap = 0;
    graph[to][graph_size[to]].rev = graph_size[from]-1;
    graph_size[to]++;
}

int bfs(int s, int t){
    memset(level_graph, -1, sizeof(int)*(total_nodes));
    int q[10000];
    int front=0, rear=0;
    q[rear++] = s;
    level_graph[s] = 0;
    while(front < rear){
        int u = q[front++];
        for(int i=0;i<graph_size[u];i++){
            Edge e = graph[u][i];
            if(e.cap >0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[u]+1;
                q[rear++] = e.to;
                if(e.to == t) break;
            }
        }
    }
    return level_graph[t] != -1;
}

int dfs_flow(int u, int t, int pushed){
    if(u == t) return pushed;
    for(int *cid = &ptr_graph[u]; *cid < graph_size[u]; (*cid)++){
        Edge e = graph[u][*cid];
        if(e.cap >0 && level_graph[e.to] == level_graph[u]+1){
            int tr = dfs_flow(e.to, t, pushed < e.cap ? pushed : e.cap);
            if(tr >0){
                graph[u][*cid].cap -= tr;
                graph[e.to][e.rev].cap += tr;
                return tr;
            }
        }
    }
    return 0;
}

int dinic(int s, int t){
    int flow =0;
    while(bfs(s,t)){
        memset(ptr_graph, 0, sizeof(int)*(total_nodes));
        while(1){
            int pushed = dfs_flow(s, t, INF);
            if(pushed <=0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int n;
    scanf("%d", &n);
    int w[n];
    int d[n];
    for(int i=0;i<n;i++) scanf("%d %d", &w[i], &d[i]);
    int a[n][n];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int possible[n];
    memset(possible, 0, sizeof(possible));
    for(int t=0;t<n;t++){
        int W = w[t];
        for(int j=0;j<n;j++) W += a[t][j];
        int valid = 1;
        for(int i=0;i<n;i++) {
            if(i == t) continue;
            if(w[i] > W){
                valid = 0;
                break;
            }
        }
        if(!valid){
            continue;
        }
        // Build Flow Network
        memset(graph_size, 0, sizeof(graph_size));
        total_nodes = 2; // source=0, sink=1
        // Assign game nodes
        int game_start = total_nodes;
        int game_count =0;
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(i == t || j == t){
                    continue;
                }
                if(a[i][j] >0){
                    game_count++;
                }
            }
        }
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(i == t || j == t){
                    continue;
                }
                if(a[i][j] >0){
                    // game node
                    total_nodes++;
                }
            }
        }
        // Assign team nodes
        int team_start = total_nodes;
        for(int i=0;i<n;i++) {
            if(i == t) continue;
            total_nodes++;
        }
        // Reset graph
        // Add edges
        int current_game = game_start;
        int total_games =0;
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(i == t || j == t){
                    continue;
                }
                if(a[i][j] >0){
                    // game node: current_game
                    add_edge(0, current_game, a[i][j]);
                    // team nodes
                    int team_i = team_start + i - (i > t ? 1 : 0);
                    int team_j = team_start + j - (j > t ? 1 : 0);
                    add_edge(current_game, team_i, a[i][j]);
                    add_edge(current_game, team_j, a[i][j]);
                    current_game++;
                    total_games += a[i][j];
                }
            }
        }
        // Connect team nodes to sink
        for(int i=0;i<n;i++) {
            if(i == t) continue;
            int team_node = team_start + i - (i > t ? 1 : 0);
            int cap = W - w[i];
            add_edge(team_node, 1, cap);
            if(cap <0){
                valid =0;
                break;
            }
        }
        if(!valid){
            continue;
        }
        // Compute max flow
        int flow = dinic(0,1);
        if(flow >= total_games){
            possible[t] =1;
        }
    }
    int first =1;
    for(int i=0;i<n;i++) {
        if(possible[i]){
            if(!first) printf(" ");
            printf("%d", i+1);
            first =0;
        }
    }
    printf("\n");
    return 0;
}