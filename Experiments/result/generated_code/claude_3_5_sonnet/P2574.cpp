#include <stdio.h>
#include <string.h>

#define MAXN 200005

int n, m;
char s[MAXN];
int tree[MAXN<<2], lazy[MAXN<<2];

void pushup(int node) {
    tree[node] = tree[node<<1] + tree[node<<1|1];
}

void pushdown(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) >> 1;
        lazy[node<<1] ^= 1;
        lazy[node<<1|1] ^= 1;
        tree[node<<1] = (mid - l + 1) - tree[node<<1];
        tree[node<<1|1] = (r - mid) - tree[node<<1|1];
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = s[l] - '0';
        return;
    }
    int mid = (l + r) >> 1;
    build(node<<1, l, mid);
    build(node<<1|1, mid+1, r);
    pushup(node);
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        lazy[node] ^= 1;
        tree[node] = (r - l + 1) - tree[node];
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(node<<1, l, mid, ql, qr);
    if (qr > mid) update(node<<1|1, mid+1, r, ql, qr);
    pushup(node);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid) res += query(node<<1, l, mid, ql, qr);
    if (qr > mid) res += query(node<<1|1, mid+1, r, ql, qr);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s+1);
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) update(1, 1, n, l, r);
        else printf("%d\n", query(1, 1, n, l, r));
    }
    return 0;
}