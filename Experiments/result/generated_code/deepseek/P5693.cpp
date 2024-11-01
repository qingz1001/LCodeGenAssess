#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 400005

typedef long long ll;

typedef struct {
    ll sum, prefix, suffix, max_sub;
} Node;

Node tree[4 * MAXN];
ll lazy[4 * MAXN];
ll a[MAXN];

void push_up(int node) {
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].prefix = fmax(tree[node * 2].prefix, tree[node * 2].sum + tree[node * 2 + 1].prefix);
    tree[node].suffix = fmax(tree[node * 2 + 1].suffix, tree[node * 2 + 1].sum + tree[node * 2].suffix);
    tree[node].max_sub = fmax(fmax(tree[node * 2].max_sub, tree[node * 2 + 1].max_sub), tree[node * 2].suffix + tree[node * 2 + 1].prefix);
}

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        ll add = lazy[node];
        int mid = (start + end) / 2;
        tree[node * 2].sum += add * (mid - start + 1);
        tree[node * 2 + 1].sum += add * (end - mid);
        tree[node * 2].prefix += add * (mid - start + 1);
        tree[node * 2 + 1].prefix += add * (end - mid);
        tree[node * 2].suffix += add * (mid - start + 1);
        tree[node * 2 + 1].suffix += add * (end - mid);
        tree[node * 2].max_sub += add * (mid - start + 1);
        tree[node * 2 + 1].max_sub += add * (end - mid);
        lazy[node * 2] += add;
        lazy[node * 2 + 1] += add;
        lazy[node] = 0;
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = tree[node].prefix = tree[node].suffix = tree[node].max_sub = a[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        push_up(node);
    }
}

void update(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].sum += val * (end - start + 1);
        tree[node].prefix += val * (end - start + 1);
        tree[node].suffix += val * (end - start + 1);
        tree[node].max_sub += val * (end - start + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update(node * 2, start, mid, l, r, val);
    if (r > mid) update(node * 2 + 1, mid + 1, end, l, r, val);
    push_up(node);
}

Node query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return tree[node];
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (r <= mid) return query(node * 2, start, mid, l, r);
    if (l > mid) return query(node * 2 + 1, mid + 1, end, l, r);
    Node left = query(node * 2, start, mid, l, r);
    Node right = query(node * 2 + 1, mid + 1, end, l, r);
    Node result;
    result.sum = left.sum + right.sum;
    result.prefix = fmax(left.prefix, left.sum + right.prefix);
    result.suffix = fmax(right.suffix, right.sum + left.suffix);
    result.max_sub = fmax(fmax(left.max_sub, right.max_sub), left.suffix + right.prefix);
    return result;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    while (q--) {
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1) {
            ll x;
            scanf("%lld", &x);
            update(1, 1, n, l, r, x);
        } else {
            Node result = query(1, 1, n, l, r);
            printf("%lld\n", result.max_sub);
        }
    }
    return 0;
}