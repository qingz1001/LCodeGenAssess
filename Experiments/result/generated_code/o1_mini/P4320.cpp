#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 1000005
#define MAXLOG 21
#define MAXBCT 2000005

typedef struct Edge {
    int to;
    int next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v){
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int dfn[MAXN];
int low[MAXN];
int time_stamp = 0;
int is_articulation[MAXN];
int stack_edges[MAXM * 2];
int stack_top = 0;
int bcc_cnt = 0;
int bcc_id[MAXN];
int bcc_list[MAXM * 2];
int bcc_size[MAXBCT];
int ap_cnt = 0;

void tarjan(int u, int parent_u){
    dfn[u] = low[u] = ++time_stamp;
    int children = 0;
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(v == parent_u) continue;
        if(!dfn[v]){
            stack_edges[stack_top++] = i;
            tarjan(v, u);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            if(low[v] >= dfn[u]){
                if(parent_u != -1){
                    is_articulation[u] = 1;
                }
                bcc_cnt++;
                while(stack_top > 0){
                    int e = stack_edges[--stack_top];
                    int node = edges[e].to;
                    bcc_id[node] = bcc_cnt;
                    if(edges[e^1].to == u){
                        break;
                    }
                }
                children++;
            }
        }
        else{
            if(dfn[v] < dfn[u]){
                stack_edges[stack_top++] = i;
            }
            if(low[u] > dfn[v]){
                low[u] = dfn[v];
            }
        }
    }
    if(parent_u == -1 && children > 1){
        is_articulation[u] = 1;
    }
}

int bct_head[MAXBCT];
Edge bct_edges[MAXM * 4];
int bct_cnt = 0;
int articulation_node[MAXN];
int total_bct_nodes = 0;
int node_map[MAXN];

void add_bct_edge(int u, int v){
    bct_edges[bct_cnt].to = v;
    bct_edges[bct_cnt].next = bct_head[u];
    bct_head[u] = bct_cnt++;
}

int up_table[MAXLOG][MAXBCT];
int depth_bct[MAXBCT];
long long sum_articulation[MAXBCT];
int LOG;

void dfs_bct(int u, int parent_u){
    up_table[0][u] = parent_u;
    if(parent_u == -1){
        depth_bct[u] = 0;
        sum_articulation[u] = 0;
    }
    else{
        depth_bct[u] = depth_bct[parent_u] + 1;
        sum_articulation[u] = sum_articulation[parent_u];
        // Check if u is articulation
        if(u >= bcc_cnt +1){
            sum_articulation[u]++;
        }
    }
    for(int i = 1; i < LOG; i++){
        if(up_table[i-1][u] != -1){
            up_table[i][u] = up_table[i-1][up_table[i-1][u]];
        }
        else{
            up_table[i][u] = -1;
        }
    }
    for(int i = bct_head[u]; i != -1; i = bct_edges[i].next){
        int v = bct_edges[i].to;
        if(v != parent_u){
            dfs_bct(v, u);
        }
    }
}

int lca_bct(int u, int v){
    if(depth_bct[u] < depth_bct[v]){
        int tmp = u;
        u = v;
        v = tmp;
    }
    for(int k = LOG-1; k >=0; k--){
        if(up_table[k][u] != -1 && depth_bct[up_table[k][u]] >= depth_bct[v]){
            u = up_table[k][u];
        }
    }
    if(u == v){
        return u;
    }
    for(int k = LOG-1; k >=0; k--){
        if(up_table[k][u] != -1 && up_table[k][u] != up_table[k][v]){
            u = up_table[k][u];
            v = up_table[k][v];
        }
    }
    return up_table[0][u];
}

int main(){
    memset(head, -1, sizeof(head));
    memset(bct_head, -1, sizeof(bct_head));
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    tarjan(1, -1);
    // Assign articulation nodes
    total_bct_nodes = bcc_cnt;
    for(int u=1; u<=n; u++){
        if(is_articulation[u]){
            ap_cnt++;
            articulation_node[u] = total_bct_nodes + ap_cnt;
        }
    }
    // Build block-cut tree
    for(int u=1; u<=n; u++){
        if(is_articulation[u]){
            for(int i = head[u]; i != -1; i = edges[i].next){
                int v = edges[i].to;
                if(bcc_id[v] == bcc_id[u]){
                    continue;
                }
                add_bct_edge(bcc_id[u], articulation_node[u]);
                add_bct_edge(articulation_node[u], bcc_id[u]);
            }
        }
    }
    total_bct_nodes += ap_cnt;
    // Initialize LCA
    LOG = 0;
    while((1 << LOG) <= total_bct_nodes){
        LOG++;
    }
    // Perform DFS on block-cut tree
    dfs_bct(1, -1);
    // Read queries
    int q;
    scanf("%d", &q);
    while(q--){
        int u, v;
        scanf("%d %d", &u, &v);
        int bcu, bcv;
        if(is_articulation[u]){
            bcu = articulation_node[u];
        }
        else{
            bcu = bcc_id[u];
        }
        if(is_articulation[v]){
            bcv = articulation_node[v];
        }
        else{
            bcv = bcc_id[v];
        }
        int lca = lca_bct(bcu, bcv);
        long long cnt = sum_articulation[bcu] + sum_articulation[bcv] - 2 * sum_articulation[lca];
        if(lca >= bcc_cnt +1){
            cnt++;
        }
        if(is_articulation[u]){
            cnt--;
        }
        if(is_articulation[v]){
            cnt--;
        }
        printf("%lld\n", 2 + cnt);
    }
    return 0;
}