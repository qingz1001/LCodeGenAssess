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
int size_tree[MAXN], depth_tree[MAXN], parent_node[MAXN], heavy_child[MAXN];
int top_node[MAXN], in_order[MAXN], out_order[MAXN];
int current_pos = 1;
int color_init[MAXN];
int n, m;

typedef struct SegmentTreeNode {
    int l, r;
    int left_color, right_color;
    int seg;
    int lazy;
} SegmentTreeNode;

SegmentTreeNode segtree[4 * MAXN];
int A[MAXN];

void add_edge(int u, int v){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj[u];
    adj[u] = edge;
}

void dfs1(int u, int p){
    size_tree[u] = 1;
    parent_node[u] = p;
    depth_tree[u] = depth_tree[p] + 1;
    heavy_child[u] = -1;
    int max_size = 0;
    for(Edge* e = adj[u]; e != NULL; e = e->next){
        int v = e->to;
        if(v != p){
            dfs1(v, u);
            size_tree[u] += size_tree[v];
            if(size_tree[v] > max_size){
                max_size = size_tree[v];
                heavy_child[u] = v;
            }
        }
    }
}

void dfs2(int u, int topu){
    top_node[u] = topu;
    in_order[u] = current_pos;
    A[current_pos] = color_init[u];
    current_pos++;
    if(heavy_child[u] != -1){
        dfs2(heavy_child[u], topu);
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(v != parent_node[u] && v != heavy_child[u]){
                dfs2(v, v);
            }
        }
    }
}

void push_up(int node){
    segtree[node].left_color = segtree[node*2].left_color;
    segtree[node].right_color = segtree[node*2+1].right_color;
    segtree[node].seg = segtree[node*2].seg + segtree[node*2+1].seg;
    if(segtree[node*2].right_color == segtree[node*2+1].left_color){
        segtree[node].seg--;
    }
}

void build(int node, int l, int r){
    segtree[node].l = l;
    segtree[node].r = r;
    segtree[node].lazy = -1;
    if(l == r){
        segtree[node].left_color = A[l];
        segtree[node].right_color = A[l];
        segtree[node].seg = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    push_up(node);
}

void push_down(int node){
    if(segtree[node].lazy != -1){
        int c = segtree[node].lazy;
        int left = node*2;
        int right = node*2+1;
        segtree[left].left_color = c;
        segtree[left].right_color = c;
        segtree[left].seg = 1;
        segtree[left].lazy = c;
        segtree[right].left_color = c;
        segtree[right].right_color = c;
        segtree[right].seg = 1;
        segtree[right].lazy = c;
        segtree[node].lazy = -1;
    }
}

void update_range(int node, int l, int r, int c){
    if(segtree[node].l > r || segtree[node].r < l){
        return;
    }
    if(segtree[node].l >= l && segtree[node].r <= r){
        segtree[node].left_color = c;
        segtree[node].right_color = c;
        segtree[node].seg = 1;
        segtree[node].lazy = c;
        return;
    }
    push_down(node);
    update_range(node*2, l, r, c);
    update_range(node*2+1, l, r, c);
    push_up(node);
}

typedef struct Result {
    int seg;
    int left;
    int right;
} Result;

Result query_range(int node, int l, int r){
    if(segtree[node].l > r || segtree[node].r < l){
        Result res = {0, -1, -1};
        return res;
    }
    if(segtree[node].l >= l && segtree[node].r <= r){
        Result res;
        res.seg = segtree[node].seg;
        res.left = segtree[node].left_color;
        res.right = segtree[node].right_color;
        return res;
    }
    push_down(node);
    Result res1 = query_range(node*2, l, r);
    Result res2 = query_range(node*2+1, l, r);
    if(res1.left == -1){
        return res2;
    }
    if(res2.left == -1){
        return res1;
    }
    Result res;
    res.seg = res1.seg + res2.seg;
    if(res1.right == res2.left){
        res.seg--;
    }
    res.left = res1.left;
    res.right = res2.right;
    return res;
}

Result query_path(int a, int b){
    Result res;
    res.seg = 0;
    res.left = -1;
    res.right = -1;
    while(top_node[a] != top_node[b]){
        if(depth_tree[top_node[a]] < depth_tree[top_node[b]]){
            int temp = a;
            a = b;
            b = temp;
        }
        Result tmp = query_range(1, in_order[top_node[a]], in_order[a]);
        if(res.left == -1){
            res = tmp;
        }
        else{
            if(res.left != tmp.right){
                res.seg += tmp.seg;
            }
            else{
                res.seg += tmp.seg -1;
            }
            res.left = tmp.left;
            res.right = res.right;
        }
        a = parent_node[top_node[a]];
    }
    if(depth_tree[a] > depth_tree[b]){
        int temp = a;
        a = b;
        b = temp;
    }
    Result tmp = query_range(1, in_order[a], in_order[b]);
    if(res.left == -1){
        res = tmp;
    }
    else{
        if(res.right == tmp.left){
            res.seg += tmp.seg -1;
        }
        else{
            res.seg += tmp.seg;
        }
        res.right = tmp.right;
    }
    return res;
}

void update_path(int a, int b, int c){
    while(top_node[a] != top_node[b]){
        if(depth_tree[top_node[a]] < depth_tree[top_node[b]]){
            int temp = a;
            a = b;
            b = temp;
        }
        update_range(1, in_order[top_node[a]], in_order[a], c);
        a = parent_node[top_node[a]];
    }
    if(depth_tree[a] > depth_tree[b]){
        int temp = a;
        a = b;
        b = temp;
    }
    update_range(1, in_order[a], in_order[b], c);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &color_init[i]);
    for(int i=1;i<n;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for(int i=0;i<m;i++){
        char op;
        scanf(" %c", &op);
        if(op == 'C'){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            update_path(a, b, c);
        }
        else if(op == 'Q'){
            int a, b;
            scanf("%d %d", &a, &b);
            Result ans = query_path(a, b);
            printf("%d\n", ans.seg);
        }
    }
    return 0;
}