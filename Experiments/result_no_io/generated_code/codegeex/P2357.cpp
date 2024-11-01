#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct node {
    ll l, r, sum, lazy;
} node;

node tree[800005];

ll a[200005];

void build(int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    if (l == r) {
        tree[p].sum = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    tree[p].sum = tree[p * 2].sum + tree[p * 2 + 1].sum;
}

void pushdown(int p) {
    if (tree[p].lazy != 0) {
        tree[p * 2].sum += (tree[p * 2].r - tree[p * 2].l + 1) * tree[p].lazy;
        tree[p * 2 + 1].sum += (tree[p * 2 + 1].r - tree[p * 2 + 1].l + 1) * tree[p].lazy;
        tree[p * 2].lazy += tree[p].lazy;
        tree[p * 2 + 1].lazy += tree[p].lazy;
        tree[p].lazy = 0;
    }
}

void update(int p, int l, int r, ll c) {
    if (l <= tree[p].l && r >= tree[p].r) {
        tree[p].sum += (tree[p].r - tree[p].l + 1) * c;
        tree[p].lazy += c;
        return;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    if (l <= mid) update(p * 2, l, r, c);
    if (r > mid) update(p * 2 + 1, l, r, c);
    tree[p].sum = tree[p * 2].sum + tree[p * 2 + 1].sum;
}

ll query(int p, int l, int r) {
    if (l <= tree[p].l && r >= tree[p].r) {
        return tree[p].sum;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    ll ans = 0;
    if (l <= mid) ans += query(p * 2, l, r);
    if (r > mid) ans += query(p * 2 + 1, l, r);
    return ans;
}

int main() {
    int n, f;
    scanf("%d%d", &n, &f);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    for (int i = 0; i < f; i++) {
        int op;
        ll x, y;
        scanf("%d%lld", &op, &x);
        if (op == 1) {
            scanf("%lld", &y);
            update(1, x, y, x);
        } else if (op == 2) {
            update(1, 1, 1, x);
        } else if (op == 3) {
            update(1, 1, 1, -x);
        } else if (op == 4) {
            scanf("%lld", &y);
            printf("%lld\n", query(1, x, y));
        } else if (op == 5) {
            printf("%lld\n", tree[1].sum);
        }
    }
    return 0;
}