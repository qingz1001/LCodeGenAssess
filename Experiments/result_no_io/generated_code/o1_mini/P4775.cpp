#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

typedef struct Edge {
    int to;
    int edge_num;
    int c;
} Edge;

Edge adj_list[MAXN * 2];
int adj_ptr[MAXN];
int ptr_global;

int parent_node[MAXN];
int depth_node[MAXN];
int size_node[MAXN];
int heavy_node[MAXN];
int top_node_arr[MAXN];
int in_order[MAXN];
ll sum_c[MAXN];
int edge_id[MAXN];
ll top1_e_val[MAXN];
ll top2_e_val[MAXN];
int timer_global;

void add_edge(int u, int v, int e_num, int c) {
    adj_list[ptr_global].to = v;
    adj_list[ptr_global].edge_num = e_num;
    adj_list[ptr_global].c = c;
    adj_ptr[u]++;
    ptr_global++;
}

int max(int a, int b){
    return a > b ? a : b;
}

ll max_ll(ll a, ll b){
    return a > b ? a : b;
}

void dfs1(int u, int p, int c_e){
    parent_node[u] = p;
    depth_node[u] = depth_node[p] + 1;
    size_node[u] = 1;
    sum_c[u] = sum_c[p] + (ll)c_e;
    heavy_node[u] = -1;
    int max_size = 0;
    for(int i = 0; i < adj_ptr[u]; i++){
        Edge edge = adj_list[i + u * MAXN];
        if(edge.to != p){
            edge_id[edge.to] = edge.edge_num;
            dfs1(edge.to, u, edge.c);
            size_node[u] += size_node[edge.to];
            if(size_node[edge.to] > max_size){
                max_size = size_node[edge.to];
                heavy_node[u] = edge.to;
            }
        }
    }
}

void dfs2(int u, int topu){
    top_node_arr[u] = topu;
    in_order[u] = ++timer_global;
    if(heavy_node[u] != -1){
        dfs2(heavy_node[u], topu);
        for(int i = 0; i < adj_ptr[u]; i++){
            Edge edge = adj_list[i + u * MAXN];
            if(edge.to != parent_node[u] && edge.to != heavy_node[u]){
                dfs2(edge.to, edge.to);
            }
        }
    }
}

void update_path(int u, int v, ll b_i){
    while(top_node_arr[u] != top_node_arr[v]){
        if(depth_node[top_node_arr[u]] < depth_node[top_node_arr[v]]){
            int temp = u;
            u = v;
            v = temp;
        }
        int start = top_node_arr[u];
        int x = u;
        while(x != parent_node[start]){
            int e = edge_id[x];
            if(b_i > top1_e_val[e]){
                top2_e_val[e] = top1_e_val[e];
                top1_e_val[e] = b_i;
            }
            else if(b_i > top2_e_val[e]){
                top2_e_val[e] = b_i;
            }
            x = parent_node[x];
        }
        u = parent_node[start];
    }
    if(depth_node[u] > depth_node[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    int x = v;
    while(x != u){
        int e = edge_id[x];
        if(b_i > top1_e_val[e]){
            top2_e_val[e] = top1_e_val[e];
            top1_e_val[e] = b_i;
        }
        else if(b_i > top2_e_val[e]){
            top2_e_val[e] = b_i;
        }
        x = parent_node[x];
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        // Reset adjacency pointers
        for(int i = 1; i <= n; i++) adj_ptr[i] = 0;
        ptr_global = 0;
        // Read edges
        for(int i = 1; i < n; i++){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            add_edge(a, b, i, c);
            add_edge(b, a, i, c);
        }
        // Initialize HLD
        timer_global = 0;
        sum_c[1] = 0;
        depth_node[1] = 0;
        dfs1(1, 0, 0);
        dfs2(1, 1);
        // Initialize top1 and top2
        for(int i = 1; i < n; i++){
            top1_e_val[i] = LLONG_MIN;
            top2_e_val[i] = LLONG_MIN;
        }
        // Read m
        int m;
        scanf("%d", &m);
        for(int i = 0; i < m; i++){
            int x, y;
            ll v;
            scanf("%d %d %lld", &x, &y, &v);
            // Calculate sum_c on path
            // Find LCA
            int u = x, v_node = y;
            int lca = 1;
            while(top_node_arr[u] != top_node_arr[v_node]){
                if(depth_node[top_node_arr[u]] > depth_node[top_node_arr[v_node]]){
                    u = parent_node[top_node_arr[u]];
                }
                else{
                    v_node = parent_node[top_node_arr[v_node]];
                }
            }
            if(depth_node[u] < depth_node[v_node]){
                lca = u;
            }
            else{
                lca = v_node;
            }
            ll sum_path = sum_c[x] + sum_c[y] - 2 * sum_c[lca];
            ll b_i = sum_path - v;
            update_path(x, y, b_i);
        }
        // Find maximum
        ll max_val = LLONG_MIN;
        for(int i = 1; i < n; i++){
            if(top2_e_val[i] != LLONG_MIN){
                ll current = top1_e_val[i] + top2_e_val[i] - (ll)adj_list[(i-1)*2].c;
                if(current > max_val){
                    max_val = current;
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