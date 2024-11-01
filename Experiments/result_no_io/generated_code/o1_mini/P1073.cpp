#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], head_rev[MAXN];
int edge_cnt = 0;

int price[MAXN];
int n, m;

// BFS
int queue[MAXN];
int head_q, tail_q;
char reachable_from_start[MAXN];
char reachable_to_end[MAXN];

// SCC variables
int order[MAXN];
int order_cnt = 0;
int scc_id[MAXN];
int current_scc = 0;
int max_price_scc[MAXN];
int scc_count;

// Condensed graph
Edge cond_edges[MAXM * 2];
int cond_head[MAXN];
int cond_edge_cnt = 0;

// DP variables
int in_degree[MAXN];
int scc_queue[MAXN];
int s_head, s_tail;
int max_reach[MAXN];

int main(){
    // Initialize heads
    memset(head, -1, sizeof(head));
    memset(head_rev, -1, sizeof(head_rev));
    memset(cond_head, -1, sizeof(cond_head));
    
    // Read n and m
    scanf("%d %d", &n, &m);
    
    // Read prices
    for(int i=1;i<=n;i++) scanf("%d", &price[i]);
    
    // Read edges
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        edges[edge_cnt].to = y;
        edges[edge_cnt].next = head[x];
        head[x] = edge_cnt++;
        if(z == 2){
            edges[edge_cnt].to = x;
            edges[edge_cnt].next = head[y];
            head[y] = edge_cnt++;
        }
    }
    
    // BFS from 1
    head_q = 0; tail_q = 0;
    queue[tail_q++] = 1;
    reachable_from_start[1] = 1;
    while(head_q < tail_q){
        int u = queue[head_q++];
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(!reachable_from_start[v]){
                reachable_from_start[v] = 1;
                queue[tail_q++] = v;
            }
        }
    }
    
    // Build reversed graph
    edge_cnt = 0;
    // Reinitialize edges for reversed graph
    for(int i=1;i<=n;i++) head_rev[i] = -1;
    // Read edges again to build reversed graph
    // Reset input
    freopen(NULL, "r", stdin);
    // Skip first two lines
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &price[i]);
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        head_rev[y] = edge_cnt;
        edges[edge_cnt].to = x;
        edges[edge_cnt].next = head_rev[y];
        edge_cnt++;
        if(z == 2){
            head_rev[x] = edge_cnt;
            edges[edge_cnt].to = y;
            edges[edge_cnt].next = head_rev[x];
            edge_cnt++;
        }
    }
    
    // BFS from n on reversed graph
    head_q = 0; tail_q = 0;
    queue[tail_q++] = n;
    reachable_to_end[n] = 1;
    while(head_q < tail_q){
        int u = queue[head_q++];
        for(int e = head_rev[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(!reachable_to_end[v]){
                reachable_to_end[v] = 1;
                queue[tail_q++] = v;
            }
        }
    }
    
    // Restore original graph
    edge_cnt = 0;
    // Reinitialize edges for original graph
    for(int i=1;i<=n;i++) head[i] = -1;
    // Reset input
    freopen(NULL, "r", stdin);
    // Skip first two lines
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &price[i]);
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(reachable_from_start[x] && reachable_to_end[y]){
            edges[edge_cnt].to = y;
            edges[edge_cnt].next = head[x];
            head[x] = edge_cnt++;
        }
        if(z == 2){
            if(reachable_from_start[y] && reachable_to_end[x]){
                edges[edge_cnt].to = x;
                edges[edge_cnt].next = head[y];
                head[y] = edge_cnt++;
            }
        }
    }
    
    // Now perform Kosaraju's first pass (DFS to get order)
    // Implement iterative DFS
    int *stack = (int*)malloc(n * sizeof(int));
    int stack_ptr = 0;
    memset(order, 0, sizeof(order));
    memset(scc_id, 0, sizeof(scc_id));
    for(int i=1;i<=n;i++) {
        if(reachable_from_start[i] && reachable_to_end[i] && !scc_id[i]){
            // Push to stack
            stack[stack_ptr++] = i;
            scc_id[i] = -1; // Mark as visited but not assigned
            while(stack_ptr > 0){
                int u = stack[stack_ptr-1];
                int done = 1;
                for(int e = head[u]; e != -1; e = edges[e].next){
                    int v = edges[e].to;
                    if(reachable_from_start[v] && reachable_to_end[v]){
                        if(!scc_id[v]){
                            stack[stack_ptr++] = v;
                            scc_id[v] = -1;
                            done = 0;
                            break;
                        }
                    }
                }
                if(done){
                    order[order_cnt++] = stack[--stack_ptr];
                }
            }
        }
    }
    
    // Second pass on reversed graph to assign SCC
    // Reinitialize reversed edges
    edge_cnt = 0;
    for(int i=1;i<=n;i++) head_rev[i] = -1;
    // Re-read edges
    freopen(NULL, "r", stdin);
    // Skip first two lines
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &price[i]);
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(reachable_from_start[y] && reachable_to_end[x]){
            edges[edge_cnt].to = x;
            edges[edge_cnt].next = head_rev[y];
            head_rev[y] = edge_cnt++;
        }
        if(z == 2){
            if(reachable_from_start[x] && reachable_to_end[y]){
                edges[edge_cnt].to = y;
                edges[edge_cnt].next = head_rev[x];
                head_rev[x] = edge_cnt++;
            }
        }
    }
    
    // Assign SCCs
    memset(scc_id, 0, sizeof(scc_id));
    current_scc = 0;
    for(int i=order_cnt-1;i>=0;i--){
        int u = order[i];
        if(!scc_id[u]){
            current_scc++;
            // DFS on reversed graph
            stack_ptr = 0;
            stack[stack_ptr++] = u;
            scc_id[u] = current_scc;
            while(stack_ptr > 0){
                int node = stack[stack_ptr-1];
                int done = 1;
                for(int e = head_rev[node]; e != -1; e = edges[e].next){
                    int v = edges[e].to;
                    if(!scc_id[v]){
                        scc_id[v] = current_scc;
                        stack[stack_ptr++] = v;
                        done = 0;
                        break;
                    }
                }
                if(done){
                    stack_ptr--;
                }
            }
        }
    }
    free(stack);
    scc_count = current_scc;
    
    // Find max price in each SCC
    for(int i=1;i<=scc_count;i++) max_price_scc[i] = 0;
    for(int i=1;i<=n;i++) {
        if(reachable_from_start[i] && reachable_to_end[i]){
            if(price[i] > max_price_scc[scc_id[i]]) max_price_scc[scc_id[i]] = price[i];
        }
    }
    
    // Build condensed DAG
    edge_cnt = 0;
    for(int u=1; u<=n; u++) {
        if(reachable_from_start[u] && reachable_to_end[u]){
            for(int e = head[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(reachable_from_start[v] && reachable_to_end[v]){
                    if(scc_id[u] != scc_id[v]){
                        cond_edges[cond_edge_cnt].to = scc_id[v];
                        cond_edges[cond_edge_cnt].next = cond_head[scc_id[u]];
                        cond_head[scc_id[u]] = cond_edge_cnt++;
                        in_degree[scc_id[v]]++;
                    }
                }
            }
        }
    }
    
    // Topological sort using Kahn's algorithm
    memset(max_reach, 0, sizeof(max_reach));
    for(int i=1;i<=scc_count;i++) max_reach[i] = max_price_scc[i];
    s_head = 0; s_tail = 0;
    for(int i=1;i<=scc_count;i++) if(in_degree[i] == 0) scc_queue[s_tail++] = i;
    while(s_head < s_tail){
        int u = scc_queue[s_head++];
        for(int e = cond_head[u]; e != -1; e = cond_edges[e].next){
            int v = cond_edges[e].to;
            if(max_reach[v] < max_reach[u]){
                max_reach[v] = max_reach[u];
            }
            if(--in_degree[v] == 0){
                scc_queue[s_tail++] = v;
            }
        }
    }
    
    // Now find the maximum profit
    int max_profit = 0;
    // Re-read the nodes to compute max_reach[scc_id[i]] - price[i]
    // Iterate through all nodes
    for(int i=1;i<=n;i++) {
        if(reachable_from_start[i] && reachable_to_end[i]){
            int profit = max_reach[scc_id[i]] - price[i];
            if(profit > max_profit) max_profit = profit;
        }
    }
    
    printf("%d\n", max_profit);
    return 0;
}