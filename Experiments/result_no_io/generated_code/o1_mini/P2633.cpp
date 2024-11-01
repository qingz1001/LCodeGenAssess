#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXLOG 20
#define MAXSEG (2000000)

typedef struct Edge {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt = 0;

int parent_node[MAXN];
int depth_node[MAXN];
int size_node[MAXN];
int heavy[MAXN];
int top_node[MAXN];
int in_order[MAXN];
int timer_cnt = 1;

int up[MAXN][MAXLOG];

int vals[MAXN];
int sorted_vals[MAXN];
int cnt_vals = 0;

typedef struct SegTreeNode {
    int left;
    int right;
    int count;
} SegTreeNode;

SegTreeNode segtree[MAXSEG];
int seg_cnt_node = 0;
int roots_node[MAXN];

void add_edge_func(int u, int v){
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

void dfs1(int u, int p){
    parent_node[u] = p;
    size_node[u] = 1;
    int max_size = 0;
    up[u][0] = p;
    for(int i=1;i<MAXLOG;i++) {
        up[u][i] = up[ up[u][i-1] ][i-1];
    }
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            dfs1(v, u);
            size_node[u] += size_node[v];
            if(size_node[v] > max_size){
                max_size = size_node[v];
                heavy[u] = v;
            }
        }
    }
}

void dfs2(int u, int topu){
    top_node[u] = topu;
    in_order[u] = timer_cnt;
    sorted_vals[timer_cnt] = vals[u];
    timer_cnt++;
    if(heavy[u]){
        dfs2(heavy[u], topu);
        for(int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            if(v != parent_node[u] && v != heavy[u]){
                dfs2(v, v);
            }
        }
    }
}

int build(int l, int r){
    int current = seg_cnt_node++;
    segtree[current].count = 0;
    if(l != r){
        int mid = (l + r) / 2;
        segtree[current].left = build(l, mid);
        segtree[current].right = build(mid+1, r);
    }
    return current;
}

int update_seg(int prev, int l, int r, int val){
    int current = seg_cnt_node++;
    segtree[current] = segtree[prev];
    segtree[current].count +=1;
    if(l != r){
        int mid = (l + r) / 2;
        if(val <= mid){
            segtree[current].left = update_seg(segtree[prev].left, l, mid, val);
        }
        else{
            segtree[current].right = update_seg(segtree[prev].right, mid+1, r, val);
        }
    }
    return current;
}

int query_kth(int u, int v, int lca, int plca, int l, int r, int k){
    if(l == r){
        return l;
    }
    int mid = (l + r) / 2;
    int cnt = segtree[segtree[u].left].count + segtree[segtree[v].left].count - segtree[segtree[lca].left].count - segtree[segtree[plca].left].count;
    if(k <= cnt){
        return query_kth(segtree[u].left, segtree[v].left, segtree[lca].left, segtree[plca].left, l, mid, k);
    }
    else{
        return query_kth(segtree[u].right, segtree[v].right, segtree[lca].right, segtree[plca].right, mid+1, r, k - cnt);
    }
}

int lca_func(int u, int v){
    if(depth_node[u] < depth_node[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    for(int k = MAXLOG-1; k >=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            u = up[u][k];
        }
    }
    if(u == v){
        return u;
    }
    for(int k = MAXLOG-1; k >=0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return parent_node[u];
}

int main(){
    int n, m;
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &vals[i]);
        sorted_vals[i] = vals[i];
    }
    for(int i=1;i<n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge_func(x, y);
        add_edge_func(y, x);
    }
    // Coordinate compression
    memcpy(sorted_vals +1, vals +1, sizeof(int)*n);
    qsort(sorted_vals +1, n, sizeof(int), cmp);
    int unique = 1;
    for(int i=2;i<=n;i++){
        if(sorted_vals[i] != sorted_vals[unique]){
            unique++;
            sorted_vals[unique] = sorted_vals[i];
        }
    }
    for(int i=1;i<=n;i++){
        int tmp = vals[i];
        int l =1, r = unique, res =1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(sorted_vals[mid] >= tmp){
                res = mid;
                r = mid -1;
            }
            else{
                l = mid +1;
            }
        }
        vals[i] = res;
    }
    // DFS and HLD
    depth_node[1] = 0;
    dfs1(1, 1);
    dfs2(1, 1);
    // Build persistent segment tree
    roots_node[0] = build(1, unique);
    for(int i=1;i<=n;i++){
        roots_node[i] = update_seg(roots_node[i-1], 1, unique, vals[sorted_vals[i]]);
    }
    // Process queries
    long long last = 0;
    for(int i=0;i<m;i++){
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        u ^= last;
        // Find LCA
        int lca = lca_func(u, v);
        int plca = parent_node[lca];
        // Query
        int res = query_kth(roots_node[u], roots_node[v], roots_node[lca], roots_node[plca], 1, unique, k);
        last = sorted_vals[res];
        printf("%d\n", last);
    }
    return 0;
}