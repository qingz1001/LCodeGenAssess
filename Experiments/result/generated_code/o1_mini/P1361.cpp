#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 3005
#define INF 1000000000

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Edge graph[MAXN][MAXN];
int graph_size[MAXN];
int level_nodes[MAXN];
int ptr_nodes[MAXN];
int total_nodes = 0;

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

int queue_nodes[MAXN];
int front_q, back_q;

int bfs(int s, int t){
    memset(level_nodes, -1, sizeof(int)*(total_nodes+1));
    front_q = back_q = 0;
    queue_nodes[back_q++] = s;
    level_nodes[s] = 0;
    while(front_q < back_q){
        int u = queue_nodes[front_q++];
        for(int i=0;i<graph_size[u];i++){
            Edge e = graph[u][i];
            if(e.cap > 0 && level_nodes[e.to]==-1){
                level_nodes[e.to] = level_nodes[u]+1;
                queue_nodes[back_q++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *p = &ptr_nodes[u]; *p < graph_size[u]; (*p)++){
        Edge *e = &graph[u][*p];
        if(e->cap > 0 && level_nodes[e->to] == level_nodes[u]+1){
            int pushed = dfs(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed > 0){
                graph[u][*p].cap -= pushed;
                graph[e->to][e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int dinic(int s, int t){
    int flow = 0;
    while(bfs(s, t)){
        memset(ptr_nodes, 0, sizeof(int)*(total_nodes+1));
        while(1){
            int pushed = dfs(s, t, INF);
            if(pushed == 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int n;
    scanf("%d", &n);
    int a[n+1], b[n+1];
    long long sum_a=0, sum_b=0, sum_c1=0, sum_c2=0;
    for(int i=1;i<=n;i++) { scanf("%d", &a[i]); sum_a += a[i]; }
    for(int i=1;i<=n;i++) { scanf("%d", &b[i]); sum_b += b[i]; }
    int m;
    scanf("%d", &m);
    int ki, c1, c2, crops[1001];
    // Calculate total nodes: S, T, crops, 2 per combination
    total_nodes = 2 + n + 2*m;
    int S = 0, T = 1;
    int combo_start_A = 2 + n;
    for(int j=0;j<m;j++){
        scanf("%d %d %d", &ki, &c1, &c2);
        for(int k=0;k<ki;k++) scanf("%d", &crops[k]);
        int C_A = combo_start_A + 2*j;
        int C_B = combo_start_A + 2*j +1;
        // Connect S to C_A with c1
        add_edge(S, C_A, c1);
        sum_c1 += c1;
        // Connect C_A to all crops in group with INF
        for(int k=0;k<ki;k++) add_edge(C_A, 2 + crops[k]-1, INF);
        // Connect C_B to T with c2
        add_edge(C_B, T, c2);
        sum_c2 += c2;
        // Connect all crops in group to C_B with INF
        for(int k=0;k<ki;k++) add_edge(2 + crops[k]-1, C_B, INF);
    }
    // Connect S to crops with a_i and crops to T with b_i
    for(int i=0;i<n;i++){
        add_edge(S, 2+i, a[i+1]);
        add_edge(2+i, T, b[i+1]);
    }
    // Total profit
    long long total = sum_a + sum_b + sum_c1 + sum_c2;
    // Compute min-cut
    int min_cut = dinic(S, T);
    // Maximum profit
    printf("%lld\n", total - (long long)min_cut);
}