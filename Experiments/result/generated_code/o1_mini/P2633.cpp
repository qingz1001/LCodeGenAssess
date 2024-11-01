#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLOG 20
#define MAXSTNODES 2000000

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int n, m;
int weights[MAXN];
int sorted_weights[MAXN];
int unique_weights[MAXN];
int unique_cnt = 0;

int size_[MAXN], depth_[MAXN], parent_[MAXN], heavy[MAXN];
int top_[MAXN], in_[MAXN];
int timer_ = 0;

int fa[MAXN][MAXLOG];

int left_child[MAXSTNODES];
int right_child[MAXSTNODES];
int cnt_[MAXSTNODES];
int root_[MAXN];
int node_cnt = 0;

int compare_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

void add_edge(int u, int v){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

int get_id(int x){
    int l = 0, r = unique_cnt -1, mid, res = -1;
    while(l <= r){
        mid = (l + r) / 2;
        if(unique_weights[mid] >= x){
            res = mid;
            r = mid -1;
        }
        else{
            l = mid +1;
        }
    }
    return res +1;
}

int insert_pst(int prev, int l, int r, int val){
    node_cnt++;
    int cur = node_cnt;
    left_child[cur] = left_child[prev];
    right_child[cur] = right_child[prev];
    cnt_[cur] = cnt_[prev] +1;
    if(l == r) return cur;
    int mid = (l + r) / 2;
    if(val <= mid){
        left_child[cur] = insert_pst(left_child[prev], l, mid, val);
    }
    else{
        right_child[cur] = insert_pst(right_child[prev], mid+1, r, val);
    }
    return cur;
}

int query_pst(int u, int v, int lca, int plca, int l, int r, int k){
    if(l == r) return l;
    int cnt_left = cnt_[left_child[u]] + cnt_[left_child[v]] - cnt_[left_child[lca]] - cnt_[left_child[plca]];
    int mid = (l + r) / 2;
    if(cnt_left >= k){
        return query_pst(left_child[u], left_child[v], left_child[lca], left_child[plca], l, mid, k);
    }
    else{
        return query_pst(right_child[u], right_child[v], right_child[lca], right_child[plca], mid+1, r, k - cnt_left);
    }
}

void dfs1(int u, int p){
    size_[u] = 1;
    parent_[u] = p;
    fa[u][0] = p;
    depth_[u] = depth_[p] +1;
    heavy[u] = -1;
    Edge* e = adj[u];
    while(e){
        int v = e->to;
        if(v != p){
            dfs1(v, u);
            size_[u] += size_[v];
            if(heavy[u] == -1 || size_[v] > size_[heavy[u]]){
                heavy[u] = v;
            }
        }
        e = e->next;
    }
}

void dfs2(int u, int topf){
    top_[u] = topf;
    in_[u] = ++timer_;
    if(heavy[u] != -1){
        dfs2(heavy[u], topf);
        Edge* e = adj[u];
        while(e){
            int v = e->to;
            if(v != parent_[u] && v != heavy[u]){
                dfs2(v, v);
            }
            e = e->next;
        }
    }
}

int lca_query(int u, int v){
    while(top_[u] != top_[v]){
        if(depth_[top_[u]] < depth_[top_[v]]){
            v = parent_[top_[v]];
        }
        else{
            u = parent_[top_[u]];
        }
    }
    return depth_[u] < depth_[v] ? u : v;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &weights[i]);
        sorted_weights[i-1] = weights[i];
    }
    qsort(sorted_weights, n, sizeof(int), compare_int);
    unique_cnt = 0;
    unique_weights[unique_cnt++] = sorted_weights[0];
    for(int i=1;i<n;i++) if(sorted_weights[i] != sorted_weights[i-1]){
        unique_weights[unique_cnt++] = sorted_weights[i];
    }
    for(int i=1;i<n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    // Initialize persistent segment trees
    root_[0] = 0;
    node_cnt = 0;
    for(int i=1;i<=n;i++){
        if(parent_[i] == 0){
            root_[i] = insert_pst(root_[parent_[i]], 1, unique_cnt, get_id(weights[i]));
        }
        else{
            root_[i] = insert_pst(root_[parent_[i]], 1, unique_cnt, get_id(weights[i]));
        }
    }
    // LCA binary lifting
    for(int j=1; j<MAXLOG; j++) {
        for(int i=1;i<=n;i++) {
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }
    int last = 0;
    while(m--){
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u ^= last;
        int lca_uv = lca_query(u, v);
        int plca = parent_[lca_uv];
        int res_id = query_pst(root_[u], root_[v], root_[lca_uv], root_[plca], 1, unique_cnt, k);
        last = unique_weights[res_id-1];
        printf("%d\n", last);
    }
    return 0;
}