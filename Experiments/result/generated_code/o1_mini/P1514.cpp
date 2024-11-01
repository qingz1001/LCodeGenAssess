#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 500
#define MAX_N 500
#define MAX_BITS 512
#define MAX_WORDS (MAX_BITS / 64)
#define MAX_CELLS (MAX_N * MAX_M)
#define INF 1000000000

typedef struct {
    int x;
    int y;
    int height;
    int index;
} Cell;

typedef struct {
    int to, rev;
    int cap, cost;
} Edge;

typedef struct {
    Edge edges[1000000];
    int head[MAX_CELLS + 2];
    int cnt;
} Graph;

Graph graph;

void init_graph() {
    memset(graph.head, -1, sizeof(graph.head));
    graph.cnt = 0;
}

void add_edge(int from, int to, int cap, int cost){
    graph.edges[graph.cnt].to = to;
    graph.edges[graph.cnt].cap = cap;
    graph.edges[graph.cnt].cost = cost;
    graph.edges[graph.cnt].rev = graph.cnt + 1;
    graph.cnt++;
    
    graph.edges[graph.cnt].to = from;
    graph.edges[graph.cnt].cap = 0;
    graph.edges[graph.cnt].cost = -cost;
    graph.edges[graph.cnt].rev = graph.cnt -1;
    graph.cnt++;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int total = N * M;
    Cell cells[MAX_CELLS];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%d", &cells[i*M + j].height);
            cells[i*M + j].x = i;
            cells[i*M + j].y = j;
            cells[i*M + j].index = i*M + j;
        }
    }
    // Sort cells in descending order of height
    for(int i=0;i<total-1;i++){
        for(int j=i+1;j<total;j++){
            if(cells[i].height < cells[j].height){
                Cell temp = cells[i];
                cells[i] = cells[j];
                cells[j] = temp;
            }
        }
    }
    // Initialize bitsets
    unsigned long long bitsets[MAX_CELLS][MAX_WORDS];
    memset(bitsets, 0, sizeof(bitsets));
    for(int i=0;i<total;i++){
        if(cells[i].x == 0){
            int row1_id = cells[i].y;
            bitsets[cells[i].index][row1_id / 64] |= 1ULL << (row1_id % 64);
        }
        // For each lower neighbor, propagate the bits
        int x = cells[i].x;
        int y = cells[i].y;
        // 4 directions
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];
            if(nx >=0 && nx < N && ny >=0 && ny < M){
                int neighbor = nx * M + ny;
                if(cells[i].height > cells[neighbor].height){
                    for(int w=0; w<MAX_WORDS; w++) {
                        bitsets[neighbor][w] |= bitsets[cells[i].index][w];
                    }
                }
            }
        }
    }
    // Collect reachability for rowN nodes
    int rowN = N-1;
    int unreachable = 0;
    // Prepare bipartite graph
    // Left nodes: 0 to M-1 (row1)
    // Right nodes: M to 2M-1 (rowN)
    // Source: 2M
    // Sink: 2M+1
    init_graph();
    int S = 2*M;
    int T = 2*M+1;
    int total_right = M;
    for(int j=0; j<M; j++){
        add_edge(S, j, 1, 1); // Cost 1 to select pump
    }
    for(int j=0; j<M; j++){
        int cell_idx = rowN * M + j;
        int has = 0;
        for(int w=0; w<MAX_WORDS; w++) {
            if(bitsets[cell_idx][w]){
                for(int b=0; b<64; b++) {
                    if((bitsets[cell_idx][w] >> b) & 1){
                        int row1_id = w * 64 + b;
                        if(row1_id < M){
                            add_edge(row1_id, M + j, 1, 0);
                            has = 1;
                        }
                    }
                }
            }
        }
        if(!has){
            unreachable++;
        }
    }
    if(unreachable > 0){
        printf("0\n%d\n", unreachable);
        return 0;
    }
    for(int j=0; j<M; j++){
        add_edge(M + j, T, 1, 0);
    }
    // Min Cost Max Flow using SPFA
    int V = 2*M + 2;
    int prevv[V];
    int preve[V];
    int dist[V];
    int inqueue[V];
    int flow = 0;
    int cost = 0;
    while(1){
        for(int i=0;i<V;i++) dist[i] = INF;
        memset(inqueue, 0, sizeof(inqueue));
        dist[S] = 0;
        int q[V];
        int head_q=0, tail_q=0;
        q[tail_q++] = S;
        inqueue[S] = 1;
        while(head_q < tail_q){
            int u = q[head_q++];
            inqueue[u] = 0;
            for(int e_idx = graph.head[u]; e_idx != -1; e_idx = graph.edges[e_idx].to == T ? -1 : graph.edges[e_idx].rev){
                Edge e = graph.edges[e_idx];
                if(e.cap > 0 && dist[e.to] > dist[u] + e.cost){
                    dist[e.to] = dist[u] + e.cost;
                    prevv[e.to] = u;
                    preve[e.to] = e_idx;
                    if(!inqueue[e.to]){
                        q[tail_q++] = e.to;
                        inqueue[e.to] = 1;
                    }
                }
            }
        }
        if(dist[T] == INF) break;
        // Find minimum possible flow
        int d = INF;
        int vtx = T;
        while(vtx != S){
            int u = prevv[vtx];
            int e_idx = preve[vtx];
            d = d < graph.edges[e_idx].cap ? d : graph.edges[e_idx].cap;
            vtx = u;
        }
        flow += d;
        cost += d * dist[T];
        vtx = T;
        while(vtx != S){
            int u = prevv[vtx];
            int e_idx = preve[vtx];
            graph.edges[e_idx].cap -= d;
            graph.edges[graph.edges[e_idx].rev].cap += d;
            vtx = u;
        }
    }
    // Check if all rowN nodes are covered
    if(flow < M){
        printf("0\n%d\n", M - flow);
    }
    else{
        printf("1\n%d\n", cost);
    }
    return 0;
}