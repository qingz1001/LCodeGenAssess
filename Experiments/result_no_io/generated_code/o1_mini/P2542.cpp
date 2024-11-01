#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30005
#define MAX_M 100005
#define MAX_OP 40005
#define MAX_LOG 16

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int op;
    int u;
    int v;
} Operation;

typedef struct {
    int to, next;
} AdjEdge;

Edge edges[MAX_M];
Operation ops[MAX_OP];
int op_cnt = 0;

AdjEdge adj_final[2 * MAX_M];
int head_final[MAX_N];
int edge_cnt_final = 0;

int deleted[MAX_M];

int n, m;

// For sorting edges
int cmp_edge(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    int ua = ea->u < ea->v ? ea->u : ea->v;
    int va = ea->u < ea->v ? ea->v : ea->u;
    int ub = eb->u < eb->v ? eb->u : eb->v;
    int vb = eb->u < eb->v ? eb->v : eb->u;
    if (ua != ub) return ua - ub;
    return va - vb;
}

// Union-Find for 2ECC
int parent_2ecc[MAX_N];
int find_2ecc(int x){
    if(parent_2ecc[x]!=x) parent_2ecc[x] = find_2ecc(parent_2ecc[x]);
    return parent_2ecc[x];
}

void union_2ecc(int x, int y){
    int fx = find_2ecc(x);
    int fy = find_2ecc(y);
    if(fx != fy){
        parent_2ecc[fx] = fy;
    }
}

// Bridge finding using Tarjan
int disc[MAX_N], low[MAX_N], time_dfs;
int is_bridge[MAX_M];
int stack_e[2 * MAX_M], top_e;
Edge bridge_edges[MAX_M];
int bridge_cnt = 0;

void add_edge_final(int u, int v){
    adj_final[edge_cnt_final].to = v;
    adj_final[edge_cnt_final].next = head_final[u];
    head_final[u] = edge_cnt_final++;
}

void tarjan_bridge(int u, int parent_edge){
    disc[u] = low[u] = ++time_dfs;
    for(int i = head_final[u]; i != -1; i = adj_final[i].next){
        int v = adj_final[i].to;
        if(i == parent_edge) continue;
        if(!disc[v]){
            tarjan_bridge(v, i ^ 1);
            if(low[v] > disc[u]){
                // Bridge found
                is_bridge[i/2] = 1;
            }
            if(low[v] < low[u]){
                low[u] = low[v];
            }
        }
        else{
            if(disc[v] < low[u]){
                low[u] = disc[v];
            }
        }
    }
}

int adj_bridge[2 * MAX_M];
int head_bridge[MAX_N];
int edge_cnt_bridge = 0;

void add_bridge(int u, int v){
    head_bridge[u] = edge_cnt_bridge;
    adj_bridge[edge_cnt_bridge++] = v;
    head_bridge[v] = edge_cnt_bridge;
    adj_bridge[edge_cnt_bridge++] = u;
}

// Bridge Tree
int parent_tree[MAX_N];
int depth_tree[MAX_N];
int anc[MAX_LOG][MAX_N];

// DFS for Bridge Tree
void dfs_tree(int u, int p){
    anc[0][u] = p;
    for(int k=1; k<MAX_LOG; k++) {
        if(anc[k-1][u] != -1)
            anc[k][u] = anc[k-1][anc[k-1][u]];
        else
            anc[k][u] = -1;
    }
    for(int i = head_bridge[u]; i < edge_cnt_bridge; i++){
        int v = adj_bridge[i];
        if(v != p){
            depth_tree[v] = depth_tree[u] + 1;
            dfs_tree(v, u);
        }
    }
}

// LCA
int get_lca(int u, int v){
    if(depth_tree[u] < depth_tree[v]){
        int tmp = u;
        u = v;
        v = tmp;
    }
    for(int k=MAX_LOG-1; k>=0; k--){
        if(depth_tree[u] - (1<<k) >= depth_tree[v]){
            u = anc[k][u];
        }
    }
    if(u == v) return u;
    for(int k=MAX_LOG-1; k>=0; k--){
        if(anc[k][u] != -1 && anc[k][u] != anc[k][v]){
            u = anc[k][u];
            v = anc[k][v];
        }
    }
    return anc[0][u];
}

int main(){
    // Initialize
    memset(head_final, -1, sizeof(head_final));
    memset(is_bridge, 0, sizeof(is_bridge));
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }
    // Sort edges for binary search
    qsort(edges, m, sizeof(Edge), cmp_edge);
    // Read operations
    while(1){
        int op, u, v;
        scanf("%d", &op);
        if(op == -1) break;
        if(op == 0 || op ==1){
            scanf("%d %d", &u, &v);
            // Find the edge index
            int low_e = 0, high_e = m-1, mid, found = -1;
            int a = u < v ? u : v;
            int b = u < v ? v : u;
            while(low_e <= high_e){
                mid = (low_e + high_e)/2;
                int ua = edges[mid].u < edges[mid].v ? edges[mid].u : edges[mid].v;
                int va = edges[mid].u < edges[mid].v ? edges[mid].v : edges[mid].u;
                if(ua == a && va == b){
                    found = mid;
                    break;
                }
                if(ua < a || (ua == a && va < b)) low_e = mid +1;
                else high_e = mid -1;
            }
            if(op ==0 && found != -1){
                deleted[found] = 1;
            }
            ops[op_cnt].op = op;
            ops[op_cnt].u = u;
            ops[op_cnt].v = v;
            op_cnt++;
        }
        else{
            ops[op_cnt].op = op;
            ops[op_cnt].u = 0;
            ops[op_cnt].v = 0;
            op_cnt++;
        }
    }
    // Build final graph
    for(int i=0; i<m; i++){
        if(!deleted[i]){
            add_edge_final(edges[i].u, edges[i].v);
            add_edge_final(edges[i].v, edges[i].u);
        }
    }
    // Find bridges in final graph
    time_dfs = 0;
    for(int i=1; i<=n; i++) if(!disc[i]) tarjan_bridge(i, -1);
    // Initialize Union-Find for 2ECC
    for(int i=1; i<=n; i++) parent_2ecc[i] = i;
    // Union non-bridge edges
    for(int i=0; i<m; i++) {
        if(!deleted[i] && !is_bridge[i]){
            union_2ecc(edges[i].u, edges[i].v);
        }
    }
    // Build Bridge Tree
    memset(head_bridge, -1, sizeof(head_bridge));
    edge_cnt_bridge = 0;
    for(int i=0; i<m; i++) {
        if(!deleted[i] && is_bridge[i]){
            int fu = find_2ecc(edges[i].u);
            int fv = find_2ecc(edges[i].v);
            if(fu != fv){
                add_bridge(fu, fv);
                add_bridge(fv, fu);
            }
        }
    }
    // Initialize bridge tree
    memset(anc, -1, sizeof(anc));
    depth_tree[find_2ecc(1)] = 0;
    dfs_tree(find_2ecc(1), -1);
    // Reverse operations
    // Prepare answers
    int total_queries = 0;
    for(int i=0; i<op_cnt; i++) if(ops[i].op ==1) total_queries++;
    int answers[total_queries];
    int ans_idx = total_queries -1;
    // Process operations in reverse
    for(int i=op_cnt-1; i>=0; i--){
        if(ops[i].op == -1) continue;
        if(ops[i].op ==1){
            int u = ops[i].u;
            int v = ops[i].v;
            int fu = find_2ecc(u);
            int fv = find_2ecc(v);
            if(fu == fv){
                answers[ans_idx--] = 0;
                continue;
            }
            int lca = get_lca(fu, fv);
            int cnt = depth_tree[fu] + depth_tree[fv] - 2 * depth_tree[lca];
            answers[ans_idx--] = cnt;
        }
        else if(ops[i].op ==0){
            int u = ops[i].u;
            int v = ops[i].v;
            // Add the edge u-v
            // Check if they are in same 2ECC
            int fu = find_2ecc(u);
            int fv = find_2ecc(v);
            if(fu != fv){
                // It's a bridge
                union_2ecc(fu, fv);
                int new_f = find_2ecc(fu);
                // Connect bridge tree
                // Set one as parent of the other
                // Here, set fv's root to fu's root
                // Update depth and ancestors
                // Attach fv to fu
                anc[0][fv] = fu;
                depth_tree[fv] = depth_tree[fu] +1;
                for(int k=1; k<MAX_LOG; k++) {
                    if(anc[k-1][fv] != -1)
                        anc[k][fv] = anc[k-1][anc[k-1][fv]];
                    else
                        anc[k][fv] = -1;
                }
            }
            // else, it's a non-bridge, do nothing
        }
    }
    // Print answers
    for(int i=0; i<total_queries; i++) printf("%d\n", answers[i]);
    return 0;
}