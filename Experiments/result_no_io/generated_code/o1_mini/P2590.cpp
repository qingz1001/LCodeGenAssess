#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 30005
#define MAXQ 200005

typedef long long ll;

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
int n, q;
int w[MAXN];
int parent_node[MAXN], depth_node[MAXN], size_subtree[MAXN];
int heavy[MAXN], head[MAXN], pos[MAXN];
int current_pos;
ll seg_sum[4*MAXN];
int seg_max[4*MAXN];

void add_edge(int a, int b){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = b;
    edge->next = graph[a];
    graph[a] = edge;
}

void dfs1(int u, int p){
    parent_node[u] = p;
    size_subtree[u] = 1;
    int max_size = 0;
    heavy[u] = -1;
    Edge* edge = graph[u];
    while(edge){
        int v = edge->to;
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            dfs1(v, u);
            size_subtree[u] += size_subtree[v];
            if(size_subtree[v] > max_size){
                max_size = size_subtree[v];
                heavy[u] = v;
            }
        }
        edge = edge->next;
    }
}

void dfs2(int u, int h){
    head[u] = h;
    pos[u] = current_pos++;
    if(heavy[u] != -1){
        dfs2(heavy[u], h);
        Edge* edge = graph[u];
        while(edge){
            int v = edge->to;
            if(v != parent_node[u] && v != heavy[u]){
                dfs2(v, v);
            }
            edge = edge->next;
        }
    }
}

void build_sum(int node, int l, int r, int arr[]){
    if(l == r){
        seg_sum[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build_sum(node*2, l, mid, arr);
    build_sum(node*2+1, mid+1, r, arr);
    seg_sum[node] = seg_sum[node*2] + seg_sum[node*2+1];
}

void build_max(int node, int l, int r, int arr[]){
    if(l == r){
        seg_max[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build_max(node*2, l, mid, arr);
    build_max(node*2+1, mid+1, r, arr);
    if(seg_max[node*2] > seg_max[node*2+1]){
        seg_max[node] = seg_max[node*2];
    }
    else{
        seg_max[node] = seg_max[node*2+1];
    }
}

void update_sum(int node, int l, int r, int idx, int val){
    if(l == r){
        seg_sum[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(idx <= mid){
        update_sum(node*2, l, mid, idx, val);
    }
    else{
        update_sum(node*2+1, mid+1, r, idx, val);
    }
    seg_sum[node] = seg_sum[node*2] + seg_sum[node*2+1];
}

void update_max(int node, int l, int r, int idx, int val){
    if(l == r){
        seg_max[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(idx <= mid){
        update_max(node*2, l, mid, idx, val);
    }
    else{
        update_max(node*2+1, mid+1, r, idx, val);
    }
    if(seg_max[node*2] > seg_max[node*2+1]){
        seg_max[node] = seg_max[node*2];
    }
    else{
        seg_max[node] = seg_max[node*2+1];
    }
}

ll query_sum(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return 0;
    }
    if(ql <= l && r <= qr){
        return seg_sum[node];
    }
    int mid = (l + r) / 2;
    return query_sum(node*2, l, mid, ql, qr) + query_sum(node*2+1, mid+1, r, ql, qr);
}

int query_max(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return -30005;
    }
    if(ql <= l && r <= qr){
        return seg_max[node];
    }
    int mid = (l + r) / 2;
    int left = query_max(node*2, l, mid, ql, qr);
    int right = query_max(node*2+1, mid+1, r, ql, qr);
    return left > right ? left : right;
}

ll path_sum(int u, int v){
    ll res = 0;
    while(head[u] != head[v]){
        if(depth_node[head[u]] < depth_node[head[v]]){
            int tmp = u;
            u = v;
            v = tmp;
        }
        res += query_sum(1, 1, n, pos[head[u]], pos[u]);
        u = parent_node[head[u]];
    }
    if(depth_node[u] > depth_node[v]){
        int tmp = u;
        u = v;
        v = tmp;
    }
    res += query_sum(1, 1, n, pos[u], pos[v]);
    return res;
}

int path_max(int u, int v){
    int res = -30005;
    while(head[u] != head[v]){
        if(depth_node[head[u]] < depth_node[head[v]]){
            int tmp = u;
            u = v;
            v = tmp;
        }
        int tmp = query_max(1, 1, n, pos[head[u]], pos[u]);
        if(tmp > res) res = tmp;
        u = parent_node[head[u]];
    }
    if(depth_node[u] > depth_node[v]){
        int tmp = u;
        u = v;
        v = tmp;
    }
    int tmp = query_max(1, 1, n, pos[u], pos[v]);
    if(tmp > res) res = tmp;
    return res;
}

int main(){
    int a, b;
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    for(int i=1;i<=n;i++){
        scanf("%d", &w[i]);
    }
    current_pos = 1;
    dfs1(1, -1);
    dfs2(1, 1);
    int arr_sum[MAXN];
    int arr_max[MAXN];
    for(int i=1;i<=n;i++){
        arr_sum[pos[i]] = w[i];
        arr_max[pos[i]] = w[i];
    }
    build_sum(1, 1, n, arr_sum);
    build_max(1, 1, n, arr_max);
    scanf("%d", &q);
    char cmd[10];
    for(int i=0;i<q;i++){
        scanf("%s", cmd);
        if(strcmp(cmd, "CHANGE") == 0){
            scanf("%d %d", &a, &b);
            update_sum(1, 1, n, pos[a], b);
            update_max(1, 1, n, pos[a], b);
        }
        else if(strcmp(cmd, "QMAX") == 0){
            scanf("%d %d", &a, &b);
            printf("%d\n", path_max(a, b));
        }
        else if(strcmp(cmd, "QSUM") == 0){
            scanf("%d %d", &a, &b);
            printf("%lld\n", path_sum(a, b));
        }
    }
    return 0;
}