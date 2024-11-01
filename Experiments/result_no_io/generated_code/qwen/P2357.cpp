#include <stdio.h>
#include <stdlib.h>

#define MAXN 200010
#define LL long long

struct Node {
    int l, r;
    LL sum, lazy;
} tree[MAXN << 2];

void pushup(int u) {
    tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum;
}

void pushdown(int u) {
    if (tree[u].lazy != 0) {
        tree[u << 1].sum += tree[u].lazy * (tree[u << 1].r - tree[u << 1].l + 1);
        tree[u << 1 | 1].sum += tree[u].lazy * (tree[u << 1 | 1].r - tree[u << 1 | 1].l + 1);
        tree[u << 1].lazy += tree[u].lazy;
        tree[u << 1 | 1].lazy += tree[u].lazy;
        tree[u].lazy = 0;
    }
}

void build(int u, int l, int r) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) {
        scanf("%lld", &tree[u].sum);
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, LL k) {
    if (l <= tree[u].l && r >= tree[u].r) {
        tree[u].sum += k * (tree[u].r - tree[u].l + 1);
        tree[u].lazy += k;
        return;
    }
    pushdown(u);
    int mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

LL query(int u, int l, int r) {
    if (l <= tree[u].l && r >= tree[u].r) {
        return tree[u].sum;
    }
    pushdown(u);
    int mid = (tree[u].l + tree[u].r) >> 1;
    LL res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

int main() {
    int n, f;
    scanf("%d %d", &n, &f);
    build(1, 1, n);
    for (int i = 0; i < f; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1 || op == 2) {
            int l, r;
            LL k;
            scanf("%d %d %lld", &l, &r, &k);
            if (op == 1) update(1, l, r, k);
            else update(1, 1, 1, k);
        } else if (op == 3) {
            int k;
            scanf("%d", &k);
            update(1, 1, 1, -k);
        } else if (op == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(1, l, r));
        } else {
            printf("%lld\n", query(1, 1, 1));
        }
    }
    return 0;
}