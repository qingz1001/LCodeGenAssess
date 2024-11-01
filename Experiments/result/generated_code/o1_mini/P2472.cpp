#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1202
#define MAXM 100000
#define INF 1000000

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Edge graph[MAXN][MAXN];
int graph_size[MAXN];
int level_graph[MAXN];
int ptr_graph[MAXN];

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

int q[MAXN];
int bfs(int s, int t){
    memset(level_graph, -1, sizeof(int)*(MAXN));
    int qh=0, qt=0;
    q[qt++] = s;
    level_graph[s] = 0;
    while(qh < qt){
        int u = q[qh++];
        for(int i=0;i<graph_size[u];i++){
            Edge e = graph[u][i];
            if(e.cap >0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[u]+1;
                q[qt++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return level_graph[t]!=-1;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *i=&ptr_graph[u]; *i < graph_size[u]; (*i)++){
        Edge e = graph[u][*i];
        if(e.cap >0 && level_graph[e.to] == level_graph[u]+1){
            int pushed = dfs(e.to, t, flow < e.cap ? flow : e.cap);
            if(pushed >0){
                graph[u][*i].cap -= pushed;
                graph[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int dinic(int s, int t){
    int flow =0;
    while(bfs(s,t)){
        memset(ptr_graph, 0, sizeof(int)*(MAXN));
        while(1){
            int pushed = dfs(s,t,INF);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int r, c, d;
    scanf("%d %d %d", &r, &c, &d);
    int h[r][c];
    char line[c+1];
    for(int i=0;i<r;i++){
        scanf("%s", line);
        for(int j=0;j<c;j++) h[i][j] = line[j]-'0';
    }
    char grid[r][c+1];
    for(int i=0;i<r;i++) scanf("%s", grid[i]);
    // Collect lizards
    int total_lizards=0;
    int lizards[r*c][2];
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(grid[i][j] == 'L'){
                lizards[total_lizards][0] = i;
                lizards[total_lizards][1] = j;
                total_lizards++;
            }
        }
    }
    // Node indexing
    // 0: source, 1: sink
    // 2 to 2+total_lizards-1: lizards
    // 2+total_lizards to 2+total_lizards + r*c -1: cell_in
    // 2+total_lizards + r*c to 2+total_lizards + 2*r*c -1: cell_out
    int source = 0, sink =1;
    int cell_in_start = 2 + total_lizards;
    int cell_out_start = cell_in_start + r*c;
    // Add edges from source to lizards
    for(int i=0;i<total_lizards;i++) {
        add_edge(source, 2+i, 1);
    }
    // Add edges from lizards to their starting cell_in
    for(int i=0;i<total_lizards;i++) {
        int li = lizards[i][0];
        int lj = lizards[i][1];
        int cell_in = cell_in_start + li*c + lj;
        add_edge(2+i, cell_in, 1);
    }
    // Add edges for cells
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(h[i][j] >0){
                int cell_in = cell_in_start + i*c + j;
                int cell_out = cell_out_start + i*c + j;
                add_edge(cell_in, cell_out, h[i][j]);
                // If boundary, connect to sink
                if(i==0 || i==r-1 || j==0 || j==c-1){
                    add_edge(cell_out, sink, h[i][j]);
                }
                // Connect to other cells within distance d
                for(int ni=0; ni<r; ni++) {
                    for(int nj=0; nj<c; nj++) {
                        if(h[ni][nj] >0){
                            if((i - ni)*(i - ni)+(j - nj)*(j - nj) <= d*d){
                                if(!(ni ==i && nj ==j)){
                                    int neighbor_in = cell_in_start + ni*c + nj;
                                    add_edge(cell_out, neighbor_in, h[ni][nj]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int max_flow = dinic(source, sink);
    printf("%d\n", total_lizards - max_flow);
}