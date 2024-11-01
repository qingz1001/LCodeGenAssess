#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

#define MAXN 100005

typedef struct Edge {
    int to;
    ll c;
    int next;
} Edge;

Edge edges_list[MAXN * 2];
int head_list[MAXN];
int edge_cnt;

int n, m;
ll v_i;
int T;

// HLD variables
int parent_node[MAXN];
int depth_node[MAXN];
int size_node[MAXN];
int heavy[MAXN];
int head_hld[MAXN];
int pos_hld[MAXN];
ll value_hld[MAXN];
int current_pos;
ll C_e_values[MAXN];
ll sum_path;
ll edge_max1[MAXN];
ll edge_max2[MAXN];

// Segment Tree
ll segtree[4 * MAXN];
int seg_n;

// Functions for HLD
void add_edge(int a, int b, ll c){
    edges_list[edge_cnt].to = b;
    edges_list[edge_cnt].c = c;
    edges_list[edge_cnt].next = head_list[a];
    head_list[a] = edge_cnt++;
}

int dfs1(int u, int p){
    parent_node[u] = p;
    size_node[u] = 1;
    depth_node[u] = depth_node[p] + 1;
    int max_size = -1;
    heavy[u] = -1;
    for(int i = head_list[u]; i != -1; i = edges_list[i].next){
        int v = edges_list[i].to;
        if(v != p){
            dfs1(v, u);
            size_node[u] += size_node[v];
            if(size_node[v] > max_size){
                max_size = size_node[v];
                heavy[u] = v;
            }
        }
    }
    return size_node[u];
}

void dfs2(int u, int h){
    head_hld[u] = h;
    pos_hld[u] = current_pos;
    current_pos++;
    if(heavy[u] != -1){
        dfs2(heavy[u], h);
        for(int i = head_list[u]; i != -1; i = edges_list[i].next){
            int v = edges_list[i].to;
            if(v != parent_node[u] && v != heavy[u]){
                dfs2(v, v);
            }
        }
    }
}

ll query_sum(int a, int b){
    ll res = 0;
    while(head_hld[a] != head_hld[b]){
        if(depth_node[head_hld[a]] > depth_node[head_hld[b]]){
            a ^= b; b ^= a; a ^= b;
        }
        // Assume segtree is built for sum
        int l = pos_hld[head_hld[b]];
        int r = pos_hld[b];
        // Sum from l to r
        // Implemented in segment tree
        // Placeholder, actual implementation needed
        // Not used since we compute sum during HLD traversal
        b = parent_node[head_hld[b]];
    }
    if(depth_node[a] > depth_node[b]){
        a ^= b; b ^= a; a ^= b;
    }
    // Sum from pos_hld[a]+1 to pos_hld[b]
    // Because edges are associated with child nodes
    // Placeholder, actual implementation needed
    return 0;
}

// Function to compute sum on path and collect edges
ll get_sum_and_collect(int u, int v, ll *sum, int *path_edges, int *path_len){
    ll total = 0;
    int len = 0;
    while(head_hld[u] != head_hld[v]){
        if(depth_node[head_hld[u]] > depth_node[head_hld[v]]){
            // Add edges from u to head_hld[u]
            // Placeholder
            u = parent_node[head_hld[u]];
        }
        else{
            // Add edges from v to head_hld[v]
            // Placeholder
            v = parent_node[head_hld[v]];
        }
    }
    if(u == v){
        // Do nothing
    }
    else{
        if(depth_node[u] > depth_node[v]){
            // Add edges from v to u
            // Placeholder
        }
        else{
            // Add edges from u to v
            // Placeholder
        }
    }
    *sum = total;
    *path_len = len;
    return total;
}

int main(){
    scanf("%d", &T);
    while(T--){
        // Initialize
        edge_cnt = 0;
        memset(head_list, -1, sizeof(int)*(n+1));
        scanf("%d", &n);
        for(int i=0;i<n-1;i++){
            int a, b;
            ll c;
            scanf("%d %d %lld", &a, &b, &c);
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        // HLD
        current_pos = 1;
        dfs1(1, 0);
        dfs2(1, 1);
        // Compute C_e for each edge based on pos_hld
        // Not implemented
        scanf("%d", &m);
        // Initialize edge_max
        for(int i=1;i<=n-1;i++){
            edge_max1[i] = LLONG_MIN;
            edge_max2[i] = LLONG_MIN;
        }
        for(int i=0;i<m;i++){
            int x, y;
            ll v;
            scanf("%d %d %lld", &x, &y, &v);
            // Compute sum on path x to y
            // Placeholder: actual sum computation needed
            ll S_i = 0;
            // Collect edges on path
            // Placeholder: actual edge collection needed
            int path_edges_list[MAXN];
            int path_len = 0;
            // Placeholder: collect edges on path and compute S_i
            // For now, skip
            // Update edge_max1 and edge_max2
            ll val = S_i - v;
            for(int j=0; j<path_len; j++){
                int e = path_edges_list[j];
                if(val > edge_max1[e]){
                    edge_max2[e] = edge_max1[e];
                    edge_max1[e] = val;
                }
                else if(val > edge_max2[e]){
                    edge_max2[e] = val;
                }
            }
        }
        // Find maximum
        ll max_val = LLONG_MIN;
        for(int i=1;i<=n-1;i++){
            if(edge_max2[i] != LLONG_MIN){
                ll temp = edge_max1[i] + edge_max2[i] - C_e_values[i];
                if(temp > max_val){
                    max_val = temp;
                }
            }
        }
        if(max_val == LLONG_MIN){
            printf("F\n");
        }
        else{
            printf("%lld\n", max_val);
        }
    }
    return 0;
}