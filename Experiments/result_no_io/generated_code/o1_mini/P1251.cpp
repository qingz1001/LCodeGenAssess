#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 2004
#define MAXM 8000
#define INF 100000000000LL

typedef long long ll;

typedef struct Edge {
    int to;
    int rev;
    ll capacity;
    ll cost;
} Edge;

Edge graph[MAXN][MAXM];
int graph_size[MAXN];
int head_node = 0;
int sink_node;
int N;
ll r[2005];
ll p, m, f, n, s;

// Queue for SPFA
int queue_nodes[MAXN];
int front, rear;
int in_queue[MAXN];
ll dist_val[MAXN];
int prevv[MAXN];
int preve[MAXN];

void add_edge(int from, int to, ll capacity, ll cost){
    Edge forward = {to, graph_size[to], capacity, cost};
    Edge backward = {from, graph_size[from], 0, -cost};
    graph[from][graph_size[from]++] = forward;
    graph[to][graph_size[to]++] = backward;
}

int main(){
    // Read input
    scanf("%d", &N);
    for(int i=1;i<=N;i++) scanf("%lld", &r[i]);
    scanf("%lld %lld %lld %lld %lld", &p, &m, &f, &n, &s);
    
    sink_node = N + 1;
    
    // Initialize graph sizes
    for(int i=0;i<=sink_node;i++) graph_size[i] = 0;
    
    // Build graph
    for(int i=1;i<=N;i++){
        // From source (0) to day i: purchase
        add_edge(0, i, r[i], p);
        // From day i to sink
        add_edge(i, sink_node, r[i], 0);
        // From day j = i - m to i: fast wash
        if(i - (int)m >=1){
            add_edge(i - (int)m, i, r[i], f);
        }
        // From day j = i - n to i: slow wash
        if(i - (int)n >=1){
            add_edge(i - (int)n, i, r[i], s);
        }
    }
    
    ll total_cost = 0;
    ll flow = 0;
    while(1){
        // Initialize for SPFA
        for(int i=0;i<=sink_node;i++) { dist_val[i] = INF; prevv[i] = -1; preve[i] = -1; }
        dist_val[0] = 0;
        front = rear = 0;
        queue_nodes[rear++] = 0;
        in_queue[0] = 1;
        
        // SPFA
        while(front < rear){
            int u = queue_nodes[front++];
            in_queue[u] = 0;
            for(int i=0;i<graph_size[u];i++){
                Edge e = graph[u][i];
                if(e.capacity >0 && dist_val[e.to] > dist_val[u] + e.cost){
                    dist_val[e.to] = dist_val[u] + e.cost;
                    prevv[e.to] = u;
                    preve[e.to] = i;
                    if(!in_queue[e.to]){
                        queue_nodes[rear++] = e.to;
                        in_queue[e.to] = 1;
                    }
                }
            }
        }
        
        if(dist_val[sink_node] == INF) break;
        
        // Find minimum possible flow to send
        ll d = INF;
        int v = sink_node;
        while(v != 0){
            int u = prevv[v];
            int e_idx = preve[v];
            if(u == -1) { d = 0; break;}
            ll cap = graph[u][e_idx].capacity;
            if(cap < d) d = cap;
            v = u;
        }
        
        if(d == 0) break;
        
        // Apply flow
        flow += d;
        total_cost += d * dist_val[sink_node];
        v = sink_node;
        while(v !=0){
            int u = prevv[v];
            int e_idx = preve[v];
            graph[u][e_idx].capacity -= d;
            // Find reverse edge
            int rev = graph[u][e_idx].rev;
            graph[v][graph[u][e_idx].to].capacity += d;
            v = u;
        }
    }
    
    printf("%lld\n", total_cost);
    return 0;
}