#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

typedef long long ll;

struct Node {
    int val;
    int lazy;
} tree[MAXN << 2];

void push_down(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        int mid = (start + end) >> 1;
        tree[node << 1].val += tree[node].lazy * (mid - start + 1);
        tree[node << 1].lazy += tree[node].lazy;
        tree[node << 1 | 1].val += tree[node].lazy * (end - mid);
        tree[node << 1 | 1].lazy += tree[node].lazy;
        tree[node].lazy = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int x) {
    if (l <= start && end <= r) {
        tree[node].val += x * (end - start + 1);
        tree[node].lazy += x;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    if (l <= mid) update_range(node << 1, start, mid, l, r, x);
    if (r > mid) update_range(node << 1 | 1, mid + 1, end, l, r, x);
    tree[node].val = tree[node << 1].val + tree[node << 1 | 1].val;
}

ll query_range(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return tree[node].val;
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    ll sum = 0;
    if (l <= mid) sum += query_range(node << 1, start, mid, l, r);
    if (r > mid) sum += query_range(node << 1 | 1, mid + 1, end, l, r);
    return sum;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tree[i + n].val);
    }
    for (int i = n - 1; i >= 1; i--) {
        tree[i].val = tree[i << 1].val + tree[i << 1 | 1].val;
    }

    while (m--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            update_range(1, 1, n, l, r, x);
        } else {
            printf("%lld\n", query_range(1, 1, n, 1, n));
        }
    }

    return 0;
}