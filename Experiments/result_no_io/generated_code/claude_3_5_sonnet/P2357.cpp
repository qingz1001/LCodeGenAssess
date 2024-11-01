#include <stdio.h>
#include <string.h>

#define MAXN 200005
#define ll long long

ll tree[MAXN * 4], lazy[MAXN * 4];
ll a[MAXN], main_tomb;
int n, f;

void pushup(int node) {
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void pushdown(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    pushup(node);
}

void update(int node, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        tree[node] += val * (r - l + 1);
        lazy[node] += val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
    pushup(node);
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    if (ql <= mid) res += query(node * 2, l, mid, ql, qr);
    if (qr > mid) res += query(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    scanf("%d %d", &n, &f);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    main_tomb = a[1];

    while (f--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            update(1, 1, n, l, r, k);
            if (l == 1) main_tomb += k;
        } else if (op == 2) {
            ll k;
            scanf("%lld", &k);
            main_tomb += k;
            update(1, 1, n, 1, 1, k);
        } else if (op == 3) {
            ll k;
            scanf("%lld", &k);
            main_tomb -= k;
            update(1, 1, n, 1, 1, -k);
        } else if (op == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        } else if (op == 5) {
            printf("%lld\n", main_tomb);
        }
    }
    return 0;
}