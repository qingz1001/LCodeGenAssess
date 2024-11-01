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
int weight[MAXN], depth[MAXN], parent[MAXN], heavy[MAXN], size[MAXN];
int chain_head[MAXN], chain_pos[MAXN], chain_idx = 0, pos_in_tree[MAXN], current_pos = 0;
int tree[MAXN * 4], max_tree[MAXN * 4];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int par, int dep) {
    depth[node] = dep;
    parent[node] = par;
    size[node] = 1;
    heavy[node] = -1;

    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == par) continue;
        dfs(to, node, dep + 1);
        size[node] += size[to];
        if (heavy[node] == -1 || size[to] > size[heavy[node]]) {
            heavy[node] = to;
        }
    }
}

void hld(int node, int head) {
    chain_head[node] = head;
    chain_pos[node] = current_pos;
    pos_in_tree[current_pos++] = node;

    if (heavy[node] != -1) {
        hld(heavy[node], head);
    }

    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == parent[node] || to == heavy[node]) continue;
        hld(to, to);
    }
}

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = weight[pos_in_tree[start]];
        max_tree[node] = weight[pos_in_tree[start]];
    } else {
        int mid = (start + end) / 2;
        build_tree(node * 2, start, mid);
        build_tree(node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
        max_tree[node] = (max_tree[node * 2] > max_tree[node * 2 + 1]) ? max_tree[node * 2] : max_tree[node * 2 + 1];
    }
}

void update_tree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        max_tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update_tree(node * 2, start, mid, idx, val);
        } else {
            update_tree(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
        max_tree[node] = (max_tree[node * 2] > max_tree[node * 2 + 1]) ? max_tree[node * 2] : max_tree[node * 2 + 1];
    }
}

int query_sum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return query_sum(node * 2, start, mid, l, r) + query_sum(node * 2 + 1, mid + 1, end, l, r);
}

int query_max(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MIN;
    }
    if (l <= start && end <= r) {
        return max_tree[node];
    }
    int mid = (start + end) / 2;
    return (query_max(node * 2, start, mid, l, r) > query_max(node * 2 + 1, mid + 1, end, l, r)) ?
           query_max(node * 2, start, mid, l, r) : query_max(node * 2 + 1, mid + 1, end, l, r);
}

int query_path_sum(int u, int v) {
    int sum = 0;
    while (chain_head[u] != chain_head[v]) {
        if (depth[chain_head[u]] < depth[chain_head[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        sum += query_sum(1, 0, current_pos - 1, chain_pos[chain_head[u]], chain_pos[u]);
        u = parent[chain_head[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    sum += query_sum(1, 0, current_pos - 1, chain_pos[u], chain_pos[v]);
    return sum;
}

int query_path_max(int u, int v) {
    int max_val = INT_MIN;
    while (chain_head[u] != chain_head[v]) {
        if (depth[chain_head[u]] < depth[chain_head[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        int current_max = query_max(1, 0, current_pos - 1, chain_pos[chain_head[u]], chain_pos[u]);
        if (current_max > max_val) {
            max_val = current_max;
        }
        u = parent[chain_head[u]];
    }
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int current_max = query_max(1, 0, current_pos - 1, chain_pos[u], chain_pos[v]);
    if (current_max > max_val) {
        max_val = current_max;
    }
    return max_val;
}

int main() {
    int n, q;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
    }

    dfs(1, -1, 0);
    hld(1, 1);
    build_tree(1, 0, current_pos - 1);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op[10];
        int u, v;
        scanf("%s %d %d", op, &u, &v);
        if (op[0] == 'C') {
            update_tree(1, 0, current_pos - 1, chain_pos[u], v);
        } else if (op[1] == 'M') {
            printf("%d\n", query_path_max(u, v));
        } else if (op[1] == 'S') {
            printf("%d\n", query_path_sum(u, v));
        }
    }

    return 0;
}