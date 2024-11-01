#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1002
#define MAXB 22
#define MAXV (1002 + 20 + 2)
#define INF 1000000000

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Edge graph[MAXV * 20000];
int head[MAXV];
int cnt;

void add_edge(int from, int to, int cap){
    graph[cnt].to = to;
    graph[cnt].cap = cap;
    graph[cnt].rev = cnt + 1;
    graph[cnt + 1].to = from;
    graph[cnt + 1].cap = 0;
    graph[cnt + 1].rev = cnt;
    head[from] = head[from]; // ensure head is accessed
    cnt +=2;
}

int level_graph[MAXV];
int ptr_graph[MAXV];
int queue_q[MAXV];
int qh, qt;

int bfs(int s, int t){
    memset(level_graph, -1, sizeof(int)*(MAXV));
    qh = 0; qt = 0;
    queue_q[qt++] = s;
    level_graph[s] = 0;
    while(qh < qt){
        int u = queue_q[qh++];
        for(int i=0;i<cnt;i++){
            if(graph[i].to == u) continue;
        }
        for(int i=0;i<cnt;i++){
            // Not efficient, need adjacency list
        }
    }
    return level_graph[t] != -1;
}

int bfs_queue[MAXV];
int bfs_level[MAXV];
int bfs_ptr;

int bfs_correct(int s, int t){
    memset(bfs_level, -1, sizeof(int)*(MAXV));
    int queue[MAXV];
    int front=0, rear=0;
    queue[rear++] = s;
    bfs_level[s] = 0;
    while(front < rear){
        int u = queue[front++];
        for(int i = head[u]; i != -1; i = -1){
            // Placeholder, need proper adjacency list
        }
    }
    return bfs_level[t] != -1;
}

typedef struct {
    int to;
    int rev;
    int cap;
} FlowEdge;

FlowEdge adj_list[MAXV][MAXB+MAXN];
int adj_size[MAXV];

void init_graph(){
    memset(head, -1, sizeof(head));
    memset(adj_size, 0, sizeof(adj_size));
    cnt = 0;
}

void add_flow_edge(int from, int to, int cap){
    adj_list[from][adj_size[from]].to = to;
    adj_list[from][adj_size[from]].cap = cap;
    adj_list[from][adj_size[from]].rev = adj_size[to];
    adj_size[from]++;
    
    adj_list[to][adj_size[to]].to = from;
    adj_list[to][adj_size[to]].cap = 0;
    adj_list[to][adj_size[to]].rev = adj_size[from]-1;
    adj_size[to]++;
}

int level[MAXV];
int ptr_ptr[MAXV];
int q_queue[MAXV];

int bfs_flow(int s, int t){
    memset(level, -1, sizeof(int)*(MAXV));
    int front=0, rear=0;
    q_queue[rear++] = s;
    level[s] = 0;
    while(front < rear){
        int u = q_queue[front++];
        for(int i=0;i<adj_size[u];i++){
            int v = adj_list[u][i].to;
            if(adj_list[u][i].cap >0 && level[v]==-1){
                level[v] = level[u]+1;
                q_queue[rear++] = v;
                if(v == t) break;
            }
        }
    }
    return level[t]!=-1;
}

int dfs_flow(int u, int t, int flow){
    if(u == t) return flow;
    for(int *p = &ptr_ptr[u]; *p < adj_size[u]; (*p)++){
        int i = *p;
        int v = adj_list[u][i].to;
        if(adj_list[u][i].cap >0 && level[v] == level[u]+1){
            int pushed = dfs_flow(v, t, (flow < adj_list[u][i].cap) ? flow : adj_list[u][i].cap);
            if(pushed >0){
                adj_list[u][i].cap -= pushed;
                adj_list[v][adj_list[u][i].rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow =0;
    while(bfs_flow(s, t)){
        memset(ptr_ptr, 0, sizeof(int)*(MAXV));
        while(1){
            int pushed = dfs_flow(s, t, INF);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int N, B;
    scanf("%d %d", &N, &B);
    int cow_pref[N][B];
    for(int i=0;i<N;i++) {
        for(int j=0;j<B;j++) {
            scanf("%d", &cow_pref[i][j]);
        }
    }
    int barn_cap[B];
    for(int i=0;i<B;i++) scanf("%d", &barn_cap[i]);
    
    // Binary search over possible range sizes
    int low = 1, high = B, answer = B;
    while(low <= high){
        int mid = (low + high)/2;
        int possible = 0;
        for(int r=1;r<=B - mid +1;r++){
            // Check if every cow has at least one barn in rankings [r, r+mid-1]
            int feasible = 1;
            // Prepare the list of allowed barns for each cow
            int allowed[N][B];
            int allowed_count[N];
            for(int i=0;i<N;i++) {
                allowed_count[i] =0;
                for(int j=r-1; j < r-1 + mid && j < B; j++) {
                    allowed[i][allowed_count[i]++] = cow_pref[i][j]-1;
                }
                if(allowed_count[i] ==0){
                    feasible =0;
                    break;
                }
            }
            if(!feasible) continue;
            // Build the flow graph
            // Nodes: 0 - source, 1..N - cows, N+1..N+B - barns, N+B+1 - sink
            int S = 0, T = N + B +1;
            init_graph();
            for(int i=0;i<N;i++) {
                add_flow_edge(i+1, S, 1);
            }
            for(int i=0;i<N;i++) {
                for(int j=0; j < allowed_count[i]; j++) {
                    add_flow_edge(i+1, N + 1 + allowed[i][j], 1);
                }
            }
            for(int i=0;i<B;i++) {
                add_flow_edge(N +1 +i, T, barn_cap[i]);
            }
            // Implement Dinic's algorithm
            // Reset adj_list and adj_size
            memset(adj_size, 0, sizeof(adj_size));
            // Rebuild adj_list
            cnt =0;
            // Re-add edges
            for(int i=0;i<N;i++) {
                add_flow_edge(S, i+1, 1);
            }
            for(int i=0;i<N;i++) {
                for(int j=0; j < allowed_count[i]; j++) {
                    add_flow_edge(i+1, N +1 + allowed[i][j], 1);
                }
            }
            for(int i=0;i<B;i++) {
                add_flow_edge(N +1 +i, T, barn_cap[i]);
            }
            // Compute max flow
            int flow = max_flow(S, T);
            if(flow == N){
                possible =1;
                break;
            }
        }
        if(possible){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    printf("%d\n", answer);
    return 0;
}