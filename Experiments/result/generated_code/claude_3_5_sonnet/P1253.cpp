#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000001
#define MAX_VAL 1000000001

typedef long long ll;

ll tree[MAX_N * 4];
ll lazy[MAX_N * 4];
int assign[MAX_N * 4];

void push_down(int node, int l, int r) {
    if (assign[node]) {
        tree[node] = lazy[node];
        if (l != r) {
            assign[node * 2] = assign[node * 2 + 1] = 1;
            lazy[node * 2] = lazy[node * 2 + 1] = lazy[node];
        }
        assign[node] = 0;
    } else if (lazy[node]) {
        tree[node] += lazy[node];
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
    }
    lazy[node] = 0;
}

void build(int node, int l, int r, ll *a) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid, a);
    build(node * 2 + 1, mid + 1, r, a);
    tree[node] = (tree[node * 2] > tree[node * 2 + 1]) ? tree[node * 2] : tree[node * 2 + 1];
}

void update_range(int node, int l, int r, int ql, int qr, ll val, int op) {
    push_down(node, l, r);
    if (ql <= l && r <= qr) {
        if (op == 1) {
            assign[node] = 1;
            lazy[node] = val;
        } else {
            lazy[node] += val;
        }
        push_down(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if (ql <= mid) update_range(node * 2, l, mid, ql, qr, val, op);
    if (qr > mid) update_range(node * 2 + 1, mid + 1, r, ql, qr, val, op);
    tree[node] = (tree[node * 2] > tree[node * 2 + 1]) ? tree[node * 2] : tree[node * 2 + 1];
}

ll query_max(int node, int l, int r, int ql, int qr) {
    push_down(node, l, r);
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    ll res = LLONG_MIN;
    if (ql <= mid) {
        ll left = query_max(node * 2, l, mid, ql, qr);
        if (left > res) res = left;
    }
    if (qr > mid) {
        ll right = query_max(node * 2 + 1, mid + 1, r, ql, qr);
        if (right > res) res = right;
    }
    return res;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    ll a[MAX_N];
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    build(1, 1, n, a);
    
    while (q--) {
        int op, l, r;
        ll x;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1 || op == 2) {
            scanf("%lld", &x);
            update_range(1, 1, n, l, r, x, op);
        } else if (op == 3) {
            printf("%lld\n", query_max(1, 1, n, l, r));
        }
    }
    
    return 0;
}