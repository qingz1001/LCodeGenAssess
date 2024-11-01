#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005

typedef struct Edge {
    int to, next;
} Edge;

Edge adj_edges[MAXN * 2];
int adj_head[MAXN];
int edge_cnt = 0;

// Function to add edge to adjacency list
void add_edge(int u, int v){
    adj_edges[edge_cnt].to = v;
    adj_edges[edge_cnt].next = adj_head[u];
    adj_head[u] = edge_cnt++;
}

int n, m, q;

// Tarjan's variables
int dfs_num[MAXN], low[MAXN];
int dfs_cnt = 0;
int is_artic[MAXN];
int stack_edges[MAXN];
int top = 0;

// Block-cut tree variables
int block_id = 0;
int total_nodes;
int bc_adj_head[MAXN];
Edge bc_edges[MAXN * 2];
int bc_cnt = 0;

void bc_add_edge(int u, int v){
    bc_edges[bc_cnt].to = v;
    bc_edges[bc_cnt].next = bc_adj_head[u];
    bc_adj_head[u] = bc_cnt++;
    bc_edges[bc_cnt].to = u;
    bc_edges[bc_cnt].next = bc_adj_head[v];
    bc_adj_head[v] = bc_cnt++;
}

// HLD variables
int parent_tree[MAXN];
int depth_tree[MAXN];
int size_tree[MAXN];
int heavy[MAXN];
int head_tree[MAXN];
int pos_tree[MAXN];
int current_pos = 1;
int flat_tree[MAXN];
int is_artic_cut[MAXN];
int segtree_size;
long long segtree[4 * MAXN];

// HLD functions
int dfs_size(int u, int parentu){
    parent_tree[u] = parentu;
    size_tree[u] = 1;
    depth_tree[u] = depth_tree[parentu] + 1;
    heavy[u] = -1;
    int max_size = 0;
    for(int e = bc_adj_head[u]; e != -1; e = bc_edges[e].next){
        int v = bc_edges[e].to;
        if(v != parentu){
            size_tree[u] += dfs_size(v, u);
            if(size_tree[v] > max_size){
                max_size = size_tree[v];
                heavy[u] = v;
            }
        }
    }
    return size_tree[u];
}

void dfs_hld(int u, int h){
    head_tree[u] = h;
    pos_tree[u] = current_pos;
    flat_tree[current_pos++] = u;
    if(heavy[u] != -1){
        dfs_hld(heavy[u], h);
        for(int e = bc_adj_head[u]; e != -1; e = bc_edges[e].next){
            int v = bc_edges[e].to;
            if(v != parent_tree[u] && v != heavy[u]){
                dfs_hld(v, v);
            }
        }
    }
}

void build_segtree(int node, int l, int r){
    if(l == r){
        segtree[node] = is_artic_cut[flat_tree[l]];
        return;
    }
    int mid = (l + r) / 2;
    build_segtree(node*2, l, mid);
    build_segtree(node*2+1, mid+1, r);
    segtree[node] = segtree[node*2] + segtree[node*2+1];
}

long long query_segtree(int node, int l, int r, int L, int R){
    if(R < l || L > r) return 0;
    if(L <= l && r <= R) return segtree[node];
    int mid = (l + r) / 2;
    return query_segtree(node*2, l, mid, L, R) + query_segtree(node*2+1, mid+1, r, L, R);
}

long long query_path(int u, int v, int total){
    long long res = 0;
    while(head_tree[u] != head_tree[v]){
        if(depth_tree[head_tree[u]] > depth_tree[head_tree[v]]){
            res += query_segtree(1, 1, total, pos_tree[head_tree[u]], pos_tree[u]);
            u = parent_tree[head_tree[u]];
        }
        else{
            res += query_segtree(1, 1, total, pos_tree[head_tree[v]], pos_tree[v]);
            v = parent_tree[head_tree[v]];
        }
    }
    if(depth_tree[u] > depth_tree[v]){
        res += query_segtree(1, 1, total, pos_tree[v], pos_tree[u]);
    }
    else{
        res += query_segtree(1, 1, total, pos_tree[u], pos_tree[v]);
    }
    return res;
}

// Tarjan's algorithm to find articulation points and build block-cut tree
void tarjan(int u, int parentu){
    dfs_num[u] = low[u] = ++dfs_cnt;
    int children = 0;
    for(int e = adj_head[u]; e != -1; e = adj_edges[e].next){
        int v = adj_edges[e].to;
        if(v == parentu) continue;
        if(!dfs_num[v]){
            stack_edges[top++] = e;
            tarjan(v, u);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            if(low[v] >= dfs_num[u]){
                if(parentu != -1) is_artic[u] = 1;
                block_id++;
                // Pop edges
                // Build block-cut tree edges
                while(top > 0){
                    int edge = stack_edges[--top];
                    int a = u, b = adj_edges[edge].to;
                    if(is_artic[a]){
                        bc_add_edge(a, n + block_id);
                    }
                    if(is_artic[b]){
                        bc_add_edge(b, n + block_id);
                    }
                    if(a == u && b == u) break;
                    if(a == u || b == u){
                        // Continue
                    }
                    if(a == parentu || b == parentu){
                        // Continue
                    }
                    if(a == u || b == u){
                        // Continue
                    }
                    if(a == u && b == parentu){
                        // Continue
                    }
                }
                // If root and has multiple children, it's already marked
            }
            children++;
        }
        else{
            if(dfs_num[v] < dfs_num[u]){
                stack_edges[top++] = e;
                low[u] = (low[u] < dfs_num[v]) ? low[u] : dfs_num[v];
            }
        }
    }
    if(parentu == -1 && children > 1){
        is_artic[u] = 1;
    }
}

int main(){
    // Fast IO
    scanf("%d %d", &n, &m);
    memset(adj_head, -1, sizeof(adj_head));
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    // Initialize block-cut tree
    memset(bc_adj_head, -1, sizeof(bc_adj_head));
    tarjan(1, -1);
    // Handle remaining stack
    while(top > 0){
        block_id++;
        while(top > 0){
            int edge = stack_edges[--top];
            int u = adj_edges[edge].to;
            // Assuming u is connected
            bc_add_edge(u, n + block_id);
            if(u == u) break;
        }
    }
    total_nodes = n + block_id;
    // Build HLD
    memset(parent_tree, 0, sizeof(parent_tree));
    memset(depth_tree, 0, sizeof(depth_tree));
    memset(size_tree, 0, sizeof(size_tree));
    memset(heavy, -1, sizeof(heavy));
    dfs_size(1, 0);
    dfs_hld(1, 1);
    // Mark articulation points
    for(int i=1;i<=n;i++) {
        is_artic_cut[i] = is_artic[i];
    }
    // Build segment tree
    build_segtree(1, 1, current_pos -1);
    // Read queries
    scanf("%d", &q);
    while(q--){
        int u, v;
        scanf("%d %d", &u, &v);
        // Map u
        int node_u = u;
        if(!is_artic[u]){
            // Find the block node
            node_u = -1;
            for(int e = adj_head[u]; e != -1; e = adj_edges[e].next){
                int b = adj_edges[e].to;
                if(is_artic[b]){
                    node_u = b;
                    break;
                }
            }
            if(node_u == -1) node_u = 1; // Fallback
        }
        // Map v
        int node_v = v;
        if(!is_artic[v]){
            // Find the block node
            node_v = -1;
            for(int e = adj_head[v]; e != -1; e = adj_edges[e].next){
                int b = adj_edges[e].to;
                if(is_artic[b]){
                    node_v = b;
                    break;
                }
            }
            if(node_v == -1) node_v = 1; // Fallback
        }
        // If u or v is not articulation and mapped to a block, ensure correct mapping
        if(!is_artic[u]){
            // Find the block node
            for(int e = adj_head[u]; e != -1; e = adj_edges[e].next){
                int b = adj_edges[e].to;
                if(b > n){
                    node_u = b;
                    break;
                }
            }
        }
        if(!is_artic[v]){
            for(int e = adj_head[v]; e != -1; e = adj_edges[e].next){
                int b = adj_edges[e].to;
                if(b > n){
                    node_v = b;
                    break;
                }
            }
        }
        // Query the path
        long long cnt = query_path(node_u, node_v, total_nodes);
        // Compute the answer
        int ans = cnt;
        if(!is_artic[u]) ans +=1;
        if(!is_artic[v] && u != v) ans +=1;
        if(u == v && !is_artic[u]) ans =1;
        printf("%d\n", ans);
    }
    return 0;
}