#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_cnt = 0;
int color[MAXN], parent[MAXN], depth[MAXN], heavy[MAXN], size[MAXN], top[MAXN], pos[MAXN], cur_pos = 0;
int n, m;

void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int node, int par, int dep) {
    parent[node] = par;
    depth[node] = dep;
    size[node] = 1;
    int max_size = 0;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != par) {
            dfs(to, node, dep + 1);
            size[node] += size[to];
            if (size[to] > max_size) {
                max_size = size[to];
                heavy[node] = to;
            }
        }
    }
}

void decompose(int node, int head_node) {
    top[node] = head_node;
    pos[node] = cur_pos++;
    if (heavy[node] != -1) {
        decompose(heavy[node], head_node);
    }
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to != parent[node] && to != heavy[node]) {
            decompose(to, to);
        }
    }
}

typedef struct {
    int l, r, color, lazy;
} SegmentTree;

SegmentTree seg_tree[MAXN * 4];

void build_tree(int node, int l, int r) {
    seg_tree[node].l = l;
    seg_tree[node].r = r;
    seg_tree[node].lazy = -1;
    if (l == r) {
        seg_tree[node].color = color[l];
    } else {
        int mid = (l + r) / 2;
        build_tree(node * 2, l, mid);
        build_tree(node * 2 + 1, mid + 1, r);
        seg_tree[node].color = seg_tree[node * 2].color + seg_tree[node * 2 + 1].color;
    }
}

void push_down(int node) {
    if (seg_tree[node].lazy != -1) {
        seg_tree[node * 2].color = seg_tree[node * 2].lazy = seg_tree[node].lazy;
        seg_tree[node * 2 + 1].color = seg_tree[node * 2 + 1].lazy = seg_tree[node].lazy;
        seg_tree[node].lazy = -1;
    }
}

void update(int node, int l, int r, int c) {
    if (seg_tree[node].l >= l && seg_tree[node].r <= r) {
        seg_tree[node].color = seg_tree[node].lazy = c;
        return;
    }
    push_down(node);
    int mid = (seg_tree[node].l + seg_tree[node].r) / 2;
    if (l <= mid) update(node * 2, l, r, c);
    if (r > mid) update(node * 2 + 1, l, r, c);
    seg_tree[node].color = seg_tree[node * 2].color + seg_tree[node * 2 + 1].color;
}

int query(int node, int l, int r) {
    if (seg_tree[node].l >= l && seg_tree[node].r <= r) {
        return seg_tree[node].color;
    }
    push_down(node);
    int mid = (seg_tree[node].l + seg_tree[node].r) / 2;
    int res = 0;
    if (l <= mid) res += query(node * 2, l, r);
    if (r > mid) res += query(node * 2 + 1, l, r);
    return res;
}

void update_path(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        update(1, pos[top[u]], pos[u], c);
        u = parent[top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    update(1, pos[u], pos[v], c);
}

int query_path(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        res += query(1, pos[top[u]], pos[u]);
        u = parent[top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    res += query(1, pos[u], pos[v]);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, -1, 0);
    decompose(1, 1);
    build_tree(1, 1, n);
    for (int i = 0; i < m; i++) {
        char op;
        int a, b, c;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %d", &a, &b, &c);
            update_path(a, b, c);
        } else if (op == 'Q') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query_path(a, b));
        }
    }
    return 0;
}