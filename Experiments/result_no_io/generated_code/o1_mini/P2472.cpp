#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 802
#define MAXM 100000
#define INF 1000000000

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Edge graph[MAXN][MAXN];
int graph_size[MAXN];
Edge edges_storage[MAXM];
int edge_count = 0;

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

int level_graph[MAXN];
int ptr_graph[MAXN];
int q[MAXN];

int bfs(int S, int T, int n){
    memset(level_graph, -1, sizeof(int)*n);
    int qf=0, qb=0;
    q[qb++] = S;
    level_graph[S] = 0;
    while(qf < qb){
        int v = q[qf++];
        for(int i=0;i<graph_size[v];i++){
            Edge e = graph[v][i];
            if(e.cap >0 && level_graph[e.to]==-1){
                level_graph[e.to] = level_graph[v]+1;
                q[qb++] = e.to;
                if(e.to == T) break;
            }
        }
    }
    return level_graph[T]!=-1;
}

int dfs(int v, int T, int flow){
    if(v == T) return flow;
    for(int *p=&ptr_graph[v]; *p < graph_size[v]; (*p)++){
        Edge *e = &graph[v][*p];
        if(e->cap >0 && level_graph[e->to] == level_graph[v]+1){
            int pushed = dfs(e->to, T, flow < e->cap ? flow : e->cap);
            if(pushed >0){
                graph[v][*p].cap -= pushed;
                graph[e->to][e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(int S, int T, int n){
    int flow =0;
    while(bfs(S, T, n)){
        memset(ptr_graph, 0, sizeof(int)*n);
        while(1){
            int pushed = dfs(S, T, INF);
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
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            scanf("%d", &h[i][j]);
        }
    }
    char line[c+2];
    int lizards[r][c];
    memset(lizards, 0, sizeof(lizards));
    for(int i=0;i<r;i++) {
        scanf("%s", line);
        for(int j=0;j<c;j++) {
            if(line[j]=='L') lizards[i][j]++;
        }
    }
    int S = r*c*2;
    int T = S+1;
    int total_lizards =0;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(h[i][j] >0){
                int node_in = (i*c +j)*2;
                int node_out = node_in +1;
                add_edge(node_in, node_out, h[i][j]);
                if(lizards[i][j] >0){
                    add_edge(S, node_in, lizards[i][j]);
                    total_lizards += lizards[i][j];
                }
                for(int x=0;x<r;x++) {
                    for(int y=0;y<c;y++) {
                        if(h[x][y] >0){
                            if((i!=x || j!=y)){
                                int dist_sq = (i-x)*(i-x) + (j-y)*(j-y);
                                if(dist_sq <= d*d){
                                    add_edge(node_out, (x*c +y)*2, INF);
                                }
                            }
                        }
                    }
                }
                int left_dist = 2*j +1;
                int right_dist = 2*c -2*j -1;
                int top_dist = 2*i +1;
                int bottom_dist = 2*r -2*i -1;
                int min_dist = left_dist;
                if(right_dist < min_dist) min_dist = right_dist;
                if(top_dist < min_dist) min_dist = top_dist;
                if(bottom_dist < min_dist) min_dist = bottom_dist;
                if(min_dist <= 2*d){
                    add_edge(node_out, T, INF);
                }
            }
        }
    }
    int n = T+1;
    int flow = max_flow(S, T, n);
    printf("%d\n", total_lizards - flow);
    return 0;
}