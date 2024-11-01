#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Node {
    int l, r;
    long long sum;
    int lazy; // -1 means no operation, 0 or 1 to set
} SegmentTree;

int n, q;
int parent_arr[MAXN];
int adj[MAXN][20]; // adjacency list
int adj_size[MAXN];
int size_arr[MAXN];
int depth_arr[MAXN];
int heavy[MAXN];
int head_arr[MAXN];
int in_arr[MAXN];
int out_arr[MAXN];
int current_pos = 0;

SegmentTree segTree[4 * MAXN];

// Initialize adjacency list
void add_edge(int u, int v){
    adj[u][adj_size[u]++] = v;
}

// DFS to compute sizes and heavy child
int dfs1(int u){
    size_arr[u] = 1;
    int max_size = 0;
    heavy[u] = -1;
    for(int i=0;i<adj_size[u];i++){
        int v = adj[u][i];
        depth_arr[v] = depth_arr[u] + 1;
        size_arr[u] += dfs1(v);
        if(size_arr[v] > max_size){
            max_size = size_arr[v];
            heavy[u] = v;
        }
    }
    return size_arr[u];
}

// DFS to assign head and in/out times
void dfs2(int u, int h){
    head_arr[u] = h;
    in_arr[u] = current_pos;
    current_pos++;
    if(heavy[u] != -1){
        dfs2(heavy[u], h);
        for(int i=0;i<adj_size[u];i++){
            int v = adj[u][i];
            if(v != heavy[u]){
                dfs2(v, v);
            }
        }
    }
    out_arr[u] = current_pos -1;
}

// Build segment tree
void build(int node, int l, int r){
    segTree[node].l = l;
    segTree[node].r = r;
    segTree[node].lazy = -1;
    if(l == r){
        segTree[node].sum = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    segTree[node].sum = segTree[2*node].sum + segTree[2*node+1].sum;
}

// Push down lazy updates
void pushdown(int node){
    if(segTree[node].lazy != -1){
        int val = segTree[node].lazy;
        segTree[2*node].sum = val * (segTree[2*node].r - segTree[2*node].l +1);
        segTree[2*node+1].sum = val * (segTree[2*node+1].r - segTree[2*node+1].l +1);
        segTree[2*node].lazy = val;
        segTree[2*node+1].lazy = val;
        segTree[node].lazy = -1;
    }
}

// Range update
void update_range(int node, int l, int r, int val){
    if(segTree[node].l > r || segTree[node].r < l){
        return;
    }
    if(segTree[node].l >= l && segTree[node].r <= r){
        segTree[node].sum = val * (segTree[node].r - segTree[node].l +1);
        segTree[node].lazy = val;
        return;
    }
    pushdown(node);
    update_range(2*node, l, r, val);
    update_range(2*node+1, l, r, val);
    segTree[node].sum = segTree[2*node].sum + segTree[2*node+1].sum;
}

// Range query
long long query_range(int node, int l, int r){
    if(segTree[node].l > r || segTree[node].r < l){
        return 0;
    }
    if(segTree[node].l >= l && segTree[node].r <= r){
        return segTree[node].sum;
    }
    pushdown(node);
    return query_range(2*node, l, r) + query_range(2*node+1, l, r);
}

// Install operation
long long install(int x){
    long long cnt = 0;
    while(x != -1){
        int h = head_arr[x];
        int l = in_arr[h];
        int r = in_arr[x];
        long long installed = query_range(1, l, r);
        cnt += (r - l +1) - installed;
        update_range(1, l, r, 1);
        if(h == 0){
            break;
        }
        x = parent_arr[h];
    }
    return cnt;
}

// Uninstall operation
long long uninstall_op(int x){
    int l = in_arr[x];
    int r = out_arr[x];
    long long s = query_range(1, l, r);
    if(s > 0){
        update_range(1, l, r, 0);
    }
    return s;
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<n;i++){
        scanf("%d", &parent_arr[i]);
        add_edge(parent_arr[i], i);
    }
    depth_arr[0] = 0;
    dfs1(0);
    dfs2(0, 0);
    build(1, 0, n-1);
    scanf("%d", &q);
    char op[10];
    int x;
    for(int i=0;i<q;i++){
        scanf("%s %d", op, &x);
        if(strcmp(op, "install") == 0){
            long long res = install(x);
            printf("%lld\n", res);
        }
        else{
            long long res = uninstall_op(x);
            printf("%lld\n", res);
        }
    }
    return 0;
}