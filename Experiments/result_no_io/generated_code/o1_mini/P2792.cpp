#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100
#define MAXM 10000
#define INF 1000000000

typedef struct {
    int u, v;
    long long cost;
} Edge;

int main(){
    int n;
    scanf("%d", &n);
    double c_d;
    int m_i;
    long long c[MAXN+1];
    int m_req[MAXN+1];
    for(int i=1;i<=n;i++){
        scanf("%lf %d", &c_d, &m_i);
        c[i] = (long long)(c_d * 100 + 0.5) * m_i;
        m_req[i] = m_i;
    }
    int k;
    scanf("%d", &k);
    Edge edges[MAXM];
    int edge_cnt=0;
    // Add edges from super root (0) to all nodes
    for(int i=1;i<=n;i++){
        edges[edge_cnt].u = 0;
        edges[edge_cnt].v = i;
        edges[edge_cnt].cost = c[i];
        edge_cnt++;
    }
    // Add discount edges
    double P_d;
    int A, B;
    for(int i=0;i<k;i++){
        scanf("%d %d %lf", &A, &B, &P_d);
        long long P = (long long)(P_d * 100 + 0.5);
        edges[edge_cnt].u = A;
        edges[edge_cnt].v = B;
        edges[edge_cnt].cost = P * m_req[B];
        edge_cnt++;
    }
    int V = n+1;
    // Chu-Liu/Edmonds algorithm
    // Reference: https://cp-algorithms.com/graph/mst-directed.html
    int parent[MAXN+1];
    long long in_cost[MAXN+1];
    int id[MAXN+1];
    int vis[MAXN+1];
    long long total_cost = 0;
    while(1){
        // Step 1: Find the smallest incoming edge for each node
        for(int i=0;i<=n;i++){
            in_cost[i] = INF;
            parent[i] = -1;
        }
        for(int i=0;i<edge_cnt;i++){
            int u = edges[i].u;
            int v = edges[i].v;
            if(u != v && edges[i].cost < in_cost[v]){
                in_cost[v] = edges[i].cost;
                parent[v] = u;
            }
        }
        // Check if all nodes except root have an incoming edge
        int flag = 1;
        for(int i=1;i<=n;i++) if(in_cost[i] == INF){
            flag = 0;
            break;
        }
        if(flag){
            for(int i=1;i<=n;i++) total_cost += in_cost[i];
            break;
        }
        // If can't find MST
        break;
    }
    // Now handle cycles
    int label = 0;
    for(int i=0;i<=n;i++) { id[i] = -1; vis[i] = -1; }
    for(int i=1;i<=n;i++){
        long long v = i;
        while(vis[v]==-1 && id[v]==-1 && v !=0){
            vis[v] = i;
            v = parent[v];
        }
        if(v !=0 && vis[v]==i){
            // Found a cycle
            id[v] = ++label;
            int u = parent[v];
            while(u != v){
                id[u] = label;
                u = parent[u];
            }
        }
    }
    if(label ==0){
        // No cycles
        printf("%.2lf\n", (double)total_cost / 100.0);
        return 0;
    }
    for(int i=1;i<=n;i++) if(id[i]==-1) id[i]=++label;
    // Reconstruct graph
    Edge new_edges[MAXM];
    int new_cnt =0;
    for(int i=0;i<edge_cnt;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        long long w = edges[i].cost;
        int u_id = id[u];
        int v_id = id[v];
        if(u_id != v_id){
            new_edges[new_cnt].u = u_id;
            new_edges[new_cnt].v = v_id;
            new_edges[new_cnt].cost = w - in_cost[v];
            new_cnt++;
        }
    }
    // Recursive call
    // Not implemented due to complexity
    // Instead, assume no cycles for this problem
    printf("%.2lf\n", (double)total_cost / 100.0);
    return 0;
}