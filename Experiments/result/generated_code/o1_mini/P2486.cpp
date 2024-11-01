#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef long long ll;

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int n, m;
int color[MAXN];
int parent_node[MAXN];
int depth_node[MAXN];
int size_node[MAXN];
int heavy[MAXN];
int head_node[MAXN];
int pos_node[MAXN];
int current_pos;
int index_map[MAXN];

typedef struct {
    int left_color;
    int right_color;
    int segments;
    int lazy; // -1 means no pending update
} SegmentTreeNode;

SegmentTreeNode segtree[4*MAXN];
int base_array[MAXN];

void add_edge(int u, int v){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj[u];
    adj[u] = edge;
}

int max(int a, int b){
    return a > b ? a : b;
}

void dfs1(int u, int p){
    parent_node[u] = p;
    size_node[u] = 1;
    heavy[u] = -1;
    int max_size = 0;
    Edge* edge = adj[u];
    while(edge){
        int v = edge->to;
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            dfs1(v, u);
            size_node[u] += size_node[v];
            if(size_node[v] > max_size){
                max_size = size_node[v];
                heavy[u] = v;
            }
        }
        edge = edge->next;
    }
}

void dfs2(int u, int h){
    head_node[u] = h;
    pos_node[u] = current_pos;
    base_array[current_pos] = color[u];
    current_pos++;
    if(heavy[u] != -1){
        dfs2(heavy[u], h);
        Edge* edge = adj[u];
        while(edge){
            int v = edge->to;
            if(v != parent_node[u] && v != heavy[u]){
                dfs2(v, v);
            }
            edge = edge->next;
        }
    }
}

void build(int node, int l, int r){
    if(l == r){
        segtree[node].left_color = base_array[l];
        segtree[node].right_color = base_array[l];
        segtree[node].segments = 1;
        segtree[node].lazy = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    segtree[node].left_color = segtree[node*2].left_color;
    segtree[node].right_color = segtree[node*2+1].right_color;
    segtree[node].segments = segtree[node*2].segments + segtree[node*2+1].segments;
    if(segtree[node*2].right_color == segtree[node*2+1].left_color){
        segtree[node].segments--;
    }
    segtree[node].lazy = -1;
}

void push_down(int node, int l, int r){
    if(segtree[node].lazy != -1){
        int color_set = segtree[node].lazy;
        int mid = (l + r) / 2;
        // Left child
        segtree[node*2].left_color = color_set;
        segtree[node*2].right_color = color_set;
        segtree[node*2].segments = 1;
        segtree[node*2].lazy = color_set;
        // Right child
        segtree[node*2+1].left_color = color_set;
        segtree[node*2+1].right_color = color_set;
        segtree[node*2+1].segments = 1;
        segtree[node*2+1].lazy = color_set;
        // Clear the lazy value
        segtree[node].lazy = -1;
    }
}

void update_range(int node, int l, int r, int u, int v, int color_set){
    if(v < l || r < u){
        return;
    }
    if(u <= l && r <= v){
        segtree[node].left_color = color_set;
        segtree[node].right_color = color_set;
        segtree[node].segments = 1;
        segtree[node].lazy = color_set;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, u, v, color_set);
    update_range(node*2+1, mid+1, r, u, v, color_set);
    segtree[node].left_color = segtree[node*2].left_color;
    segtree[node].right_color = segtree[node*2+1].right_color;
    segtree[node].segments = segtree[node*2].segments + segtree[node*2+1].segments;
    if(segtree[node*2].right_color == segtree[node*2+1].left_color){
        segtree[node].segments--;
    }
}

typedef struct {
    int left_color;
    int right_color;
    int segments;
} QueryResult;

QueryResult query_range(int node, int l, int r, int u, int v){
    if(v < l || r < u){
        QueryResult qr;
        qr.left_color = -1;
        qr.right_color = -1;
        qr.segments = 0;
        return qr;
    }
    if(u <= l && r <= v){
        QueryResult qr;
        qr.left_color = segtree[node].left_color;
        qr.right_color = segtree[node].right_color;
        qr.segments = segtree[node].segments;
        return qr;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    QueryResult ql = query_range(node*2, l, mid, u, v);
    QueryResult qr = query_range(node*2+1, mid+1, r, u, v);
    if(ql.segments == 0){
        return qr;
    }
    if(qr.segments == 0){
        return ql;
    }
    QueryResult res;
    res.left_color = ql.left_color;
    res.right_color = qr.right_color;
    res.segments = ql.segments + qr.segments;
    if(ql.right_color == qr.left_color){
        res.segments--;
    }
    return res;
}

QueryResult query_path(int a, int b){
    QueryResult res;
    res.left_color = -1;
    res.right_color = -1;
    res.segments = 0;
    while(head_node[a] != head_node[b]){
        if(depth_node[head_node[a]] > depth_node[head_node[b]]){
            QueryResult tmp = query_range(1, 0, n-1, pos_node[head_node[a]], pos_node[a]);
            if(res.segments == 0){
                res = tmp;
            }
            else{
                if(tmp.right_color == res.left_color){
                    res.segments += tmp.segments -1;
                }
                else{
                    res.segments += tmp.segments;
                }
                res.left_color = tmp.left_color;
            }
            a = parent_node[head_node[a]];
        }
        else{
            QueryResult tmp = query_range(1, 0, n-1, pos_node[head_node[b]], pos_node[b]);
            if(res.segments == 0){
                res = tmp;
            }
            else{
                if(tmp.right_color == res.left_color){
                    res.segments += tmp.segments -1;
                }
                else{
                    res.segments += tmp.segments;
                }
                res.left_color = tmp.left_color;
            }
            b = parent_node[head_node[b]];
        }
    }
    if(depth_node[a] > depth_node[b]){
        QueryResult tmp = query_range(1, 0, n-1, pos_node[b], pos_node[a]);
        if(res.segments == 0){
            res = tmp;
        }
        else{
            if(tmp.right_color == res.left_color){
                res.segments += tmp.segments -1;
            }
            else{
                res.segments += tmp.segments;
            }
            res.left_color = tmp.left_color;
        }
    }
    else{
        QueryResult tmp = query_range(1, 0, n-1, pos_node[a], pos_node[b]);
        if(res.segments == 0){
            res = tmp;
        }
        else{
            if(tmp.right_color == res.left_color){
                res.segments += tmp.segments -1;
            }
            else{
                res.segments += tmp.segments;
            }
            res.left_color = tmp.left_color;
        }
    }
    return res;
}

void update_path(int a, int b, int color_set){
    while(head_node[a] != head_node[b]){
        if(depth_node[head_node[a]] > depth_node[head_node[b]]){
            update_range(1, 0, n-1, pos_node[head_node[a]], pos_node[a], color_set);
            a = parent_node[head_node[a]];
        }
        else{
            update_range(1, 0, n-1, pos_node[head_node[b]], pos_node[b], color_set);
            b = parent_node[head_node[b]];
        }
    }
    if(depth_node[a] > depth_node[b]){
        update_range(1, 0, n-1, pos_node[b], pos_node[a], color_set);
    }
    else{
        update_range(1, 0, n-1, pos_node[a], pos_node[b], color_set);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &color[i]);
    for(int i=1;i<n;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    depth_node[1] = 0;
    dfs1(1, -1);
    current_pos = 0;
    dfs2(1, 1);
    build(1, 0, n-1);
    char op;
    for(int i=0;i<m;i++){
        scanf(" %c", &op);
        if(op == 'C'){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            update_path(a, b, c);
        }
        else if(op == 'Q'){
            int a, b;
            scanf("%d %d", &a, &b);
            QueryResult qr = query_path(a, b);
            printf("%d\n", qr.segments);
        }
    }
    return 0;
}