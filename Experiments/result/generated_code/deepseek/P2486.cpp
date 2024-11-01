#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;
int color[MAXN], parent[MAXN], depth[MAXN], heavy[MAXN], size[MAXN], top[MAXN], pos[MAXN], cur_pos;
int tree[MAXN * 4], lazy[MAXN * 4];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
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

void push_down(int node, int left, int right) {
    if (lazy[node] != -1) {
        tree[node] = lazy[node];
        if (left != right) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }
}

void update(int node, int left, int right, int ql, int qr, int value) {
    push_down(node, left, right);
    if (ql > right || qr < left) return;
    if (ql <= left && right <= qr) {
        lazy[node] = value;
        push_down(node, left, right);
        return;
    }
    int mid = (left + right) / 2;
    update(node * 2, left, mid, ql, qr, value);
    update(node * 2 + 1, mid + 1, right, ql, qr, value);
    tree[node] = tree[node * 2] == tree[node * 2 + 1] ? tree[node * 2] : -1;
}

int query(int node, int left, int right, int ql, int qr) {
    push_down(node, left, right);
    if (ql > right || qr < left) return -1;
    if (ql <= left && right <= qr) return tree[node];
    int mid = (left + right) / 2;
    int left_query = query(node * 2, left, mid, ql, qr);
    int right_query = query(node * 2 + 1, mid + 1, right, ql, qr);
    return left_query == right_query ? left_query : -1;
}

void update_path(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        update(1, 0, cur_pos - 1, pos[top[u]], pos[u], c);
        u = parent[top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    update(1, 0, cur_pos - 1, pos[u], pos[v], c);
}

int query_path(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        int prev_color = -1;
        for (int i = pos[top[u]]; i <= pos[u]; i++) {
            int cur_color = query(1, 0, cur_pos - 1, i, i);
            if (cur_color != prev_color) {
                res++;
                prev_color = cur_color;
            }
        }
        u = parent[top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int prev_color = -1;
    for (int i = pos[u]; i <= pos[v]; i++) {
        int cur_color = query(1, 0, cur_pos - 1, i, i);
        if (cur_color != prev_color) {
            res++;
            prev_color = cur_color;
        }
    }
    return res;
}

int main() {
    int n, m;
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
    for (int i = 1; i <= n; i++) {
        update(1, 0, cur_pos - 1, pos[i], pos[i], color[i]);
    }
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