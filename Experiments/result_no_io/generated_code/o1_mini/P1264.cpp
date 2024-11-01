#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 25
#define MAX_GAMES 300
#define MAX_NODES 1000
#define INF 1000000000

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Edge graph[MAX_NODES][MAX_NODES];
int graph_size[MAX_NODES];
int level_graph[MAX_NODES];
int ptr_graph[MAX_NODES];
int total_nodes;

void add_edge(int from, int to, int cap) {
    graph[from][graph_size[from]].to = to;
    graph[from][graph_size[from]].cap = cap;
    graph[from][graph_size[from]].rev = graph_size[to];
    graph[to][graph_size[to]].to = from;
    graph[to][graph_size[to]].cap = 0;
    graph[to][graph_size[to]].rev = graph_size[from];
    graph_size[from]++;
    graph_size[to]++;
}

int bfs(int s, int t) {
    memset(level_graph, -1, sizeof(int) * total_nodes);
    int q[MAX_NODES];
    int front = 0, back = 0;
    q[back++] = s;
    level_graph[s] = 0;
    while (front < back) {
        int u = q[front++];
        for(int i=0;i<graph_size[u];i++) {
            Edge *e = &graph[u][i];
            if(e->cap > 0 && level_graph[e->to]==-1){
                level_graph[e->to] = level_graph[u] +1;
                q[back++] = e->to;
                if(e->to == t) return 1;
            }
        }
    }
    return level_graph[t]!=-1;
}

int dfs_flow(int u, int t, int flow) {
    if(u == t) return flow;
    for(int *i=&ptr_graph[u]; *i < graph_size[u]; (*i)++) {
        Edge *e = &graph[u][*i];
        if(e->cap >0 && level_graph[e->to]==level_graph[u]+1){
            int pushed = dfs_flow(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed >0){
                e->cap -= pushed;
                graph[e->to][e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow =0;
    while(bfs(s,t)){
        memset(ptr_graph, 0, sizeof(int)*total_nodes);
        while(1){
            int pushed = dfs_flow(s,t,INF);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int n;
    scanf("%d", &n);
    int w[25], d[25];
    for(int i=0;i<n;i++) scanf("%d %d", &w[i], &d[i]);
    int a[25][25];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int possible[25];
    memset(possible, 0, sizeof(possible));
    for(int T=0; T<n; T++){
        int W_T_max = w[T];
        for(int j=0; j<n; j++) if(j != T) W_T_max += a[T][j];
        int flag = 1;
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            if(w[i] > W_T_max){
                flag = 0;
                break;
            }
        }
        if(!flag){
            continue;
        }
        // Build flow network
        memset(graph_size, 0, sizeof(graph_size));
        total_nodes = 2;
        // Map game pairs to nodes
        int game_start = total_nodes;
        int game_count =0;
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            for(int j=i+1;j<n;j++) {
                if(j == T) continue;
                if(a[i][j] >0){
                    game_count++;
                    add_edge(0, total_nodes, a[i][j]);
                    add_edge(total_nodes, 2 + n + game_count, a[i][j]);
                    add_edge(total_nodes, 2 + n + game_count, a[i][j]);
                    total_nodes++;
                }
            }
        }
        // Assign team nodes
        int team_nodes[25];
        int current = total_nodes;
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            team_nodes[i] = current++;
        }
        // Reset graph
        memset(graph, 0, sizeof(graph));
        memset(graph_size, 0, sizeof(graph_size));
        total_nodes = current;
        // Add edges again
        game_count =0;
        int total_game =0;
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            for(int j=i+1;j<n;j++) {
                if(j == T) continue;
                if(a[i][j] >0){
                    add_edge(0, total_nodes, a[i][j]);
                    add_edge(total_nodes, team_nodes[i], a[i][j]);
                    add_edge(total_nodes, team_nodes[j], a[i][j]);
                    total_game += a[i][j];
                    total_nodes++;
                }
            }
        }
        // Add team to sink edges
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            int cap = W_T_max - w[i];
            if(cap <0){
                flag =0;
                break;
            }
            add_edge(team_nodes[i], 1, cap);
        }
        if(!flag){
            continue;
        }
        // Compute max flow
        int flow = max_flow(0,1);
        // Calculate total_game
        int total_remaining =0;
        for(int i=0;i<n;i++) {
            if(i == T) continue;
            for(int j=i+1;j<n;j++) {
                if(j == T) continue;
                total_remaining += a[i][j];
            }
        }
        if(flow == total_remaining){
            possible[T] =1;
        }
    }
    int first=1;
    for(int i=0;i<n;i++) {
        if(possible[i]){
            if(!first) printf(" ");
            printf("%d", i+1);
            first=0;
        }
    }
    printf("\n");
    return 0;
}