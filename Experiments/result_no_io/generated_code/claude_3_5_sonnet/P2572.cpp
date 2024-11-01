#include <stdio.h>
#include <string.h>
#define MAXN 100005
#define MAXM 400005

int n, m;
int a[MAXN];

struct Node {
    int sum, lmax, rmax, max;
    int lazy_set, lazy_flip;
} tree[MAXM];

void pushup(int p) {
    int lc = p << 1, rc = (p << 1) | 1;
    tree[p].sum = tree[lc].sum + tree[rc].sum;
    tree[p].lmax = tree[lc].lmax;
    tree[p].rmax = tree[rc].rmax;
    tree[p].max = (tree[lc].rmax + tree[rc].lmax > tree[p].max) ? tree[lc].rmax + tree[rc].lmax : tree[p].max;
    if (tree[lc].lmax == tree[lc].sum) tree[p].lmax += tree[rc].lmax;
    if (tree[rc].rmax == tree[rc].sum) tree[p].rmax += tree[lc].rmax;
    if (tree[lc].max > tree[p].max) tree[p].max = tree[lc].max;
    if (tree[rc].max > tree[p].max) tree[p].max = tree[rc].max;
}

void build(int p, int l, int r) {
    tree[p].lazy_set = -1;
    tree[p].lazy_flip = 0;
    if (l == r) {
        tree[p].sum = tree[p].lmax = tree[p].rmax = tree[p].max = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build((p << 1) | 1, mid + 1, r);
    pushup(p);
}

void pushdown(int p, int l, int r) {
    int lc = p << 1, rc = (p << 1) | 1;
    int mid = (l + r) >> 1;
    if (tree[p].lazy_set != -1) {
        tree[lc].lazy_set = tree[rc].lazy_set = tree[p].lazy_set;
        tree[lc].lazy_flip = tree[rc].lazy_flip = 0;
        tree[lc].sum = tree[p].lazy_set * (mid - l + 1);
        tree[rc].sum = tree[p].lazy_set * (r - mid);
        tree[lc].lmax = tree[lc].rmax = tree[lc].max = tree[p].lazy_set ? (mid - l + 1) : 0;
        tree[rc].lmax = tree[rc].rmax = tree[rc].max = tree[p].lazy_set ? (r - mid) : 0;
        tree[p].lazy_set = -1;
    }
    if (tree[p].lazy_flip) {
        tree[lc].lazy_flip ^= 1;
        tree[rc].lazy_flip ^= 1;
        tree[lc].sum = (mid - l + 1) - tree[lc].sum;
        tree[rc].sum = (r - mid) - tree[rc].sum;
        int tmp = tree[lc].lmax;
        tree[lc].lmax = mid - l + 1 - tree[lc].rmax;
        tree[lc].rmax = mid - l + 1 - tmp;
        tree[lc].max = mid - l + 1 - tree[lc].max;
        tmp = tree[rc].lmax;
        tree[rc].lmax = r - mid - tree[rc].rmax;
        tree[rc].rmax = r - mid - tmp;
        tree[rc].max = r - mid - tree[rc].max;
        tree[p].lazy_flip = 0;
    }
}

void update(int p, int l, int r, int ql, int qr, int op) {
    if (ql <= l && r <= qr) {
        if (op < 2) {
            tree[p].lazy_set = op;
            tree[p].lazy_flip = 0;
            tree[p].sum = op * (r - l + 1);
            tree[p].lmax = tree[p].rmax = tree[p].max = op ? (r - l + 1) : 0;
        } else {
            tree[p].lazy_flip ^= 1;
            tree[p].sum = (r - l + 1) - tree[p].sum;
            int tmp = tree[p].lmax;
            tree[p].lmax = r - l + 1 - tree[p].rmax;
            tree[p].rmax = r - l + 1 - tmp;
            tree[p].max = r - l + 1 - tree[p].max;
        }
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, op);
    if (qr > mid) update((p << 1) | 1, mid + 1, r, ql, qr, op);
    pushup(p);
}

int query_sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p].sum;
    pushdown(p, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid) res += query_sum(p << 1, l, mid, ql, qr);
    if (qr > mid) res += query_sum((p << 1) | 1, mid + 1, r, ql, qr);
    return res;
}

int query_max(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p].max;
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (qr <= mid) return query_max(p << 1, l, mid, ql, qr);
    if (ql > mid) return query_max((p << 1) | 1, mid + 1, r, ql, qr);
    int lmax = query_max(p << 1, l, mid, ql, qr);
    int rmax = query_max((p << 1) | 1, mid + 1, r, ql, qr);
    int mid_max = (tree[p << 1].rmax + tree[(p << 1) | 1].lmax);
    if (mid_max > lmax) lmax = mid_max;
    return lmax > rmax ? lmax : rmax;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        l++; r++;
        if (op <= 2) update(1, 1, n, l, r, op);
        else if (op == 3) printf("%d\n", query_sum(1, 1, n, l, r));
        else printf("%d\n", query_max(1, 1, n, l, r));
    }
    return 0;
}