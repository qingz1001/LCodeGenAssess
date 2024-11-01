#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 30005
#define MAXQ 200005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int w[MAXN];
int size_node[MAXN], depth_node[MAXN], parent_node[MAXN], heavy[MAXN];
int top_node[MAXN], in_order[MAXN];
int current_in;
long long seg_sum[4 * MAXN];
int seg_max[4 * MAXN];
int n, q;

// Add edge to adjacency list
void add_edge(int a, int b) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = b;
    edge->next = adj[a];
    adj[a] = edge;
}

void dfs1(int u, int p) {
    size_node[u] = 1;
    parent_node[u] = p;
    depth_node[u] = depth_node[p] + 1;
    heavy[u] = -1;
    int max_size = 0;
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v != p) {
            dfs1(v, u);
            size_node[u] += size_node[v];
            if (size_node[v] > max_size) {
                max_size = size_node[v];
                heavy[u] = v;
            }
        }
    }
}

void dfs2(int u, int topu) {
    top_node[u] = topu;
    in_order[u] = ++current_in;
    if (heavy[u] != -1) {
        dfs2(heavy[u], topu);
        for (Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            if (v != parent_node[u] && v != heavy[u]) {
                dfs2(v, v);
            }
        }
    }
}

void build_seg(int node, int l, int r) {
    if (l == r) {
        seg_sum[node] = w[l];
        seg_max[node] = w[l];
        return;
    }
    int mid = (l + r) / 2;
    build_seg(2 * node, l, mid);
    build_seg(2 * node + 1, mid + 1, r);
    seg_sum[node] = seg_sum[2 * node] + seg_sum[2 * node + 1];
    seg_max[node] = seg_max[2 * node] > seg_max[2 * node + 1] ? seg_max[2 * node] : seg_max[2 * node + 1];
}

void update_seg(int node, int l, int r, int pos, int val) {
    if (l == r) {
        seg_sum[node] = val;
        seg_max[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update_seg(2 * node, l, mid, pos, val);
    else update_seg(2 * node + 1, mid + 1, r, pos, val);
    seg_sum[node] = seg_sum[2 * node] + seg_sum[2 * node + 1];
    seg_max[node] = seg_max[2 * node] > seg_max[2 * node + 1] ? seg_max[2 * node] : seg_max[2 * node + 1];
}

long long query_sum_seg(int node, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return seg_sum[node];
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) res += query_sum_seg(2 * node, l, mid, ql, qr);
    if (qr > mid) res += query_sum_seg(2 * node + 1, mid + 1, r, ql, qr);
    return res;
}

int query_max_seg(int node, int l, int r, int ql, int qr) {
    if (ql > qr) return -30005;
    if (ql <= l && r <= qr) return seg_max[node];
    int mid = (l + r) / 2;
    int res = -30005;
    if (ql <= mid) {
        int tmp = query_max_seg(2 * node, l, mid, ql, qr);
        if (tmp > res) res = tmp;
    }
    if (qr > mid) {
        int tmp = query_max_seg(2 * node + 1, mid + 1, r, ql, qr);
        if (tmp > res) res = tmp;
    }
    return res;
}

long long query_sum(int u, int v) {
    long long res = 0;
    while (top_node[u] != top_node[v]) {
        if (depth_node[top_node[u]] < depth_node[top_node[v]]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        res += query_sum_seg(1, 1, n, in_order[top_node[u]], in_order[u]);
        u = parent_node[top_node[u]];
    }
    if (depth_node[u] > depth_node[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    res += query_sum_seg(1, 1, n, in_order[u], in_order[v]);
    return res;
}

int query_max(int u, int v) {
    int res = -30005;
    while (top_node[u] != top_node[v]) {
        if (depth_node[top_node[u]] < depth_node[top_node[v]]) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        int tmp_max = query_max_seg(1, 1, n, in_order[top_node[u]], in_order[u]);
        if (tmp_max > res) res = tmp_max;
        u = parent_node[top_node[u]];
    }
    if (depth_node[u] > depth_node[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    int tmp_max = query_max_seg(1, 1, n, in_order[u], in_order[v]);
    if (tmp_max > res) res = tmp_max;
    return res;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    for(int i=1;i<=n;i++) scanf("%d", &w[i]);
    depth_node[0] = 0;
    dfs1(1, 0);
    dfs2(1, 1);
    int arr[MAXN];
    for(int i=1;i<=n;i++) arr[in_order[i]] = w[i];
    for(int i=1;i<=n;i++) w[i] = arr[i];
    build_seg(1, 1, n);
    scanf("%d", &q);
    char op[10];
    for(int i=0;i<q;i++){
        scanf("%s", op);
        if(strcmp(op, "CHANGE") == 0){
            int u, t;
            scanf("%d %d", &u, &t);
            update_seg(1, 1, n, in_order[u], t);
        }
        else if(strcmp(op, "QMAX") == 0){
            int u, v;
            scanf("%d %d", &u, &v);
            int res = query_max(u, v);
            printf("%d\n", res);
        }
        else if(strcmp(op, "QSUM") == 0){
            int u, v;
            scanf("%d %d", &u, &v);
            long long res = query_sum(u, v);
            printf("%lld\n", res);
        }
    }
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}