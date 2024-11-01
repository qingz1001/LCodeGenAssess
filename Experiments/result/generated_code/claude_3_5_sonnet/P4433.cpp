#include <stdio.h>
#include <string.h>

#define MAXN 100001
#define MAXQ 50001

typedef long long ll;

ll tree[MAXN * 4];
ll lazy[MAXN * 4];
int n, q;

void pushdown(int node, int l, int r) {
    if (lazy[node] == 0) return;
    int mid = (l + r) >> 1;
    tree[node * 2] += lazy[node] * (mid - l + 1);
    tree[node * 2 + 1] += lazy[node] * (r - mid);
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
}

void update(int node, int l, int r, int ql, int qr, ll a, ll b) {
    if (ql <= l && r <= qr) {
        ll val = ((ll)(l - ql + 1) * a % b + b) % b;
        tree[node] = (r - l + 1) * val;
        lazy[node] = val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(node * 2, l, mid, ql, qr, a, b);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, a, b);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += query(node * 2, l, mid, ql, qr);
    if (qr > mid) res += query(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            ll a, b;
            scanf("%lld%lld", &a, &b);
            update(1, 1, n, l, r, a, b);
        } else {
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }

    return 0;
}