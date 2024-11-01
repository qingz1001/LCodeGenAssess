#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int color[MAXN];
int head[MAXN], next[MAXM], to[MAXM], edge_count;

void add_edge(int u, int v) {
    next[edge_count] = head[u];
    head[u] = edge_count;
    to[edge_count] = v;
    edge_count++;
}

struct SegmentTree {
    int l, r;
    int color;
    int count;
    int lazy;
} tree[4 * MAXN];

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    tree[node].color = -1;
    tree[node].count = 0;
    tree[node].lazy = -1;
    if (l == r) {
        tree[node].color = color[l];
        tree[node].count = 1;
    } else {
        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        tree[node].color = tree[2 * node].color;
        tree[node].count = tree[2 * node].count + tree[2 * node + 1].count;
    }
}

void push_down(int node) {
    if (tree[node].lazy != -1) {
        tree[2 * node].color = tree[2 * node + 1].color = tree[node].lazy;
        tree[2 * node].count = tree[2 * node + 1].count = 1;
        tree[2 * node].lazy = tree[2 * node + 1].lazy = tree[node].lazy;
        tree[node].lazy = -1;
    }
}

void update(int node, int l, int r, int c) {
    if (tree[node].l > r || tree[node].r < l) {
        return;
    }
    if (tree[node].l >= l && tree[node].r <= r) {
        tree[node].color = c;
        tree[node].count = 1;
        tree[node].lazy = c;
    } else {
        push_down(node);
        int mid = (tree[node].l + tree[node].r) / 2;
        if (l <= mid) {
            update(2 * node, l, r, c);
        }
        if (r > mid) {
            update(2 * node + 1, l, r, c);
        }
        tree[node].color = tree[2 * node].color;
        tree[node].count = tree[2 * node].count + tree[2 * node + 1].count;
    }
}

int query(int node, int l, int r) {
    if (tree[node].l > r || tree[node].r < l) {
        return 0;
    }
    if (tree[node].l >= l && tree[node].r <= r) {
        return tree[node].count;
    }
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    return query(2 * node, l, r) + query(2 * node + 1, l, r);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        char op;
        int a, b, c;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %d", &a, &b, &c);
            update(1, a, b, c);
        } else if (op == 'Q') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query(1, a, b));
        }
    }
    return 0;
}