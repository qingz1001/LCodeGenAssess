#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int tree[MAXN * 4], lazy[MAXN * 4];

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    push_down(node, start, end);
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        tree[node] += val * (end - start + 1);
        if (start != end) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update_range(node * 2, start, mid, l, r, val);
    update_range(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query_range(int node, int start, int end, int l, int r) {
    push_down(node, start, end);
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return query_range(node * 2, start, mid, l, r) + query_range(node * 2 + 1, mid + 1, end, l, r);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tree[i]);
    }

    for (int i = 0; i < m; i++) {
        int type, l, r, v;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &l, &r, &v);
            update_range(1, 1, n, l, r, v);
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            printf("%d\n", query_range(1, 1, n, l, r));
        }
    }

    return 0;
}