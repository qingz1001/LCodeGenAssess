#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define ll long long

ll tree[MAXN * 4], lazy[MAXN * 4];
int n, m;

void pushup(int node) {
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void pushdown(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &tree[node]);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    pushup(node);
}

void update(int node, int l, int r, int x, int y, ll k) {
    if (x <= l && r <= y) {
        tree[node] += k * (r - l + 1);
        lazy[node] += k;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    if (x <= mid) update(node * 2, l, mid, x, y, k);
    if (y > mid) update(node * 2 + 1, mid + 1, r, x, y, k);
    pushup(node);
}

ll query(int node, int l, int r, int x, int y) {
    if (x <= l && r <= y) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    if (x <= mid) res += query(node * 2, l, mid, x, y);
    if (y > mid) res += query(node * 2 + 1, mid + 1, r, x, y);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    while (m--) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            ll k;
            scanf("%lld", &k);
            update(1, 1, n, x, y, k);
        } else {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}