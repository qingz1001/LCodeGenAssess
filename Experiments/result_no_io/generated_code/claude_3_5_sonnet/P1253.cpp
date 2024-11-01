#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000001
#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)

typedef long long ll;

ll tree[MAX_N << 2];
ll lazy[MAX_N << 2];
int flag[MAX_N << 2];

void push_up(int node) {
    tree[node] = (tree[LEFT(node)] > tree[RIGHT(node)]) ? tree[LEFT(node)] : tree[RIGHT(node)];
}

void push_down(int node, int l, int r) {
    if (flag[node]) {
        int mid = (l + r) >> 1;
        tree[LEFT(node)] = lazy[node];
        tree[RIGHT(node)] = lazy[node];
        lazy[LEFT(node)] = lazy[node];
        lazy[RIGHT(node)] = lazy[node];
        flag[LEFT(node)] = 1;
        flag[RIGHT(node)] = 1;
        flag[node] = 0;
    } else if (lazy[node]) {
        int mid = (l + r) >> 1;
        tree[LEFT(node)] += lazy[node];
        tree[RIGHT(node)] += lazy[node];
        lazy[LEFT(node)] += lazy[node];
        lazy[RIGHT(node)] += lazy[node];
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &tree[node]);
        return;
    }
    int mid = (l + r) >> 1;
    build(LEFT(node), l, mid);
    build(RIGHT(node), mid + 1, r);
    push_up(node);
}

void update1(int node, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        tree[node] = val;
        lazy[node] = val;
        flag[node] = 1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update1(LEFT(node), l, mid, ql, qr, val);
    if (qr > mid) update1(RIGHT(node), mid + 1, r, ql, qr, val);
    push_up(node);
}

void update2(int node, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update2(LEFT(node), l, mid, ql, qr, val);
    if (qr > mid) update2(RIGHT(node), mid + 1, r, ql, qr, val);
    push_up(node);
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    ll res = LLONG_MIN;
    if (ql <= mid) {
        ll left = query(LEFT(node), l, mid, ql, qr);
        res = (res > left) ? res : left;
    }
    if (qr > mid) {
        ll right = query(RIGHT(node), mid + 1, r, ql, qr);
        res = (res > right) ? res : right;
    }
    return res;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    build(1, 1, n);
    
    while (q--) {
        int op, l, r;
        ll x;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf("%lld", &x);
            update1(1, 1, n, l, r, x);
        } else if (op == 2) {
            scanf("%lld", &x);
            update2(1, 1, n, l, r, x);
        } else {
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }
    
    return 0;
}