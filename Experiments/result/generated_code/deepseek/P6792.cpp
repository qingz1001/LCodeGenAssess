#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXQ 200005

typedef struct {
    long long sum, prefix, suffix, max_sub;
} Node;

Node tree[4 * MAXN];
long long a[MAXN];

Node merge(Node left, Node right) {
    Node res;
    res.sum = left.sum + right.sum;
    res.prefix = fmax(left.prefix, left.sum + right.prefix);
    res.suffix = fmax(right.suffix, right.sum + left.suffix);
    res.max_sub = fmax(fmax(left.max_sub, right.max_sub), left.suffix + right.prefix);
    return res;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = tree[node].prefix = tree[node].suffix = tree[node].max_sub = a[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        a[idx] = val;
        tree[node].sum = tree[node].prefix = tree[node].suffix = tree[node].max_sub = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        Node null_node = {0, 0, 0, 0};
        return null_node;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    Node left = query(2 * node, start, mid, l, r);
    Node right = query(2 * node + 1, mid + 1, end, l, r);
    return merge(left, right);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    while (q--) {
        int type, l, r;
        long long x;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 0) {
            scanf("%lld", &x);
            for (int i = l; i <= r; i++) {
                if (a[i] < x) {
                    update(1, 1, n, i, x);
                }
            }
        } else {
            Node result = query(1, 1, n, l, r);
            printf("%lld\n", fmax(0, result.max_sub));
        }
    }
    return 0;
}