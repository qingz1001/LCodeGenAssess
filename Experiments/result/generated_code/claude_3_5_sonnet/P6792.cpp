#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100005
#define MAX_Q 200005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, q;
ll a[MAX_N];

struct SegmentTree {
    ll sum, lmax, rmax, max;
} tree[MAX_N * 4];

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void push_up(int node) {
    int left = node * 2, right = node * 2 + 1;
    tree[node].sum = tree[left].sum + tree[right].sum;
    tree[node].lmax = max(tree[left].lmax, tree[left].sum + tree[right].lmax);
    tree[node].rmax = max(tree[right].rmax, tree[right].sum + tree[left].rmax);
    tree[node].max = max(max(tree[left].max, tree[right].max), tree[left].rmax + tree[right].lmax);
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = tree[node].lmax = tree[node].rmax = tree[node].max = a[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    push_up(node);
}

void update(int node, int start, int end, int l, int r, ll x) {
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        if (tree[node].sum >= x * (end - start + 1)) return;
        if (tree[node].lmax < x) tree[node].lmax = x;
        if (tree[node].rmax < x) tree[node].rmax = x;
        if (tree[node].max < x) tree[node].max = x;
        tree[node].sum = max(tree[node].sum, x * (end - start + 1));
        return;
    }
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, x);
    update(node * 2 + 1, mid + 1, end, l, r, x);
    push_up(node);
}

SegmentTree query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return (SegmentTree){0, 0, 0, 0};
    if (start >= l && end <= r) return tree[node];
    int mid = (start + end) / 2;
    SegmentTree left = query(node * 2, start, mid, l, r);
    SegmentTree right = query(node * 2 + 1, mid + 1, end, l, r);
    SegmentTree result;
    result.sum = left.sum + right.sum;
    result.lmax = max(left.lmax, left.sum + right.lmax);
    result.rmax = max(right.rmax, right.sum + left.rmax);
    result.max = max(max(left.max, right.max), left.rmax + right.lmax);
    return result;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    
    for (int i = 0; i < q; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            ll x;
            scanf("%lld", &x);
            update(1, 1, n, l, r, x);
        } else {
            printf("%lld\n", max(0LL, query(1, 1, n, l, r).max));
        }
    }
    
    return 0;
}