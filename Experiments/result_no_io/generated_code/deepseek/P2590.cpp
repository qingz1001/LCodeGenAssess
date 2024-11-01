#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 30005
#define MAXQ 200005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int parent[MAXN], depth[MAXN], heavy[MAXN], size[MAXN];
int chain_top[MAXN], chain_pos[MAXN], chain_idx = 0;
int values[MAXN], n;

int tree_max[MAXN * 4], tree_sum[MAXN * 4];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    size[u] = 1;
    int max_size = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        dfs(v, u, d + 1);
        size[u] += size[v];
        if (size[v] > max_size) {
            max_size = size[v];
            heavy[u] = v;
        }
    }
}

void hld(int u, int h) {
    chain_top[u] = h;
    chain_pos[u] = chain_idx++;
    if (heavy[u] != -1) {
        hld(heavy[u], h);
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent[u] || v == heavy[u]) continue;
        hld(v, v);
    }
}

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree_max[node] = tree_sum[node] = values[start];
    } else {
        int mid = (start + end) / 2;
        build_tree(node * 2, start, mid);
        build_tree(node * 2 + 1, mid + 1, end);
        tree_max[node] = (tree_max[node * 2] > tree_max[node * 2 + 1]) ? tree_max[node * 2] : tree_max[node * 2 + 1];
        tree_sum[node] = tree_sum[node * 2] + tree_sum[node * 2 + 1];
    }
}

void update_tree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree_max[node] = tree_sum[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update_tree(node * 2, start, mid, idx, val);
        } else {
            update_tree(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree_max[node] = (tree_max[node * 2] > tree_max[node * 2 + 1]) ? tree_max[node * 2] : tree_max[node * 2 + 1];
        tree_sum[node] = tree_sum[node * 2] + tree_sum[node * 2 + 1];
    }
}

int query_max(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return INT_MIN;
    if (l <= start && end <= r) return tree_max[node];
    int mid = (start + end) / 2;
    int left_max = query_max(node * 2, start, mid, l, r);
    int right_max = query_max(node * 2 + 1, mid + 1, end, l, r);
    return (left_max > right_max) ? left_max : right_max;
}

int query_sum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree_sum[node];
    int mid = (start + end) / 2;
    return query_sum(node * 2, start, mid, l, r) + query_sum(node * 2 + 1, mid + 1, end, l, r);
}

int path_max(int u, int v) {
    int res = INT_MIN;
    while (chain_top[u] != chain_top[v]) {
        if (depth[chain_top[u]] < depth[chain_top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        int cur_max = query_max(1, 0, n - 1, chain_pos[chain_top[u]], chain_pos[u]);
        res = (res > cur_max) ? res : cur_max;
        u = parent[chain_top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int cur_max = query_max(1, 0, n - 1, chain_pos[u], chain_pos[v]);
    return (res > cur_max) ? res : cur_max;
}

int path_sum(int u, int v) {
    int res = 0;
    while (chain_top[u] != chain_top[v]) {
        if (depth[chain_top[u]] < depth[chain_top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        res += query_sum(1, 0, n - 1, chain_pos[chain_top[u]], chain_pos[u]);
        u = parent[chain_top[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    res += query_sum(1, 0, n - 1, chain_pos[u], chain_pos[v]);
    return res;
}

int main() {
    int q, a, b, u, v;
    char op[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        heavy[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        add_edge(a - 1, b - 1);
        add_edge(b - 1, a - 1);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    dfs(0, -1, 0);
    hld(0, 0);
    build_tree(1, 0, n - 1);
    scanf("%d", &q);
    while (q--) {
        scanf("%s %d %d", op, &u, &v);
        if (op[0] == 'C') {
            update_tree(1, 0, n - 1, chain_pos[u - 1], v);
        } else if (op[1] == 'M') {
            printf("%d\n", path_max(u - 1, v - 1));
        } else if (op[1] == 'S') {
            printf("%d\n", path_sum(u - 1, v - 1));
        }
    }
    return 0;
}