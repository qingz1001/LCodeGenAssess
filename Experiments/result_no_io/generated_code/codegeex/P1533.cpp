#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int l, r;
    int m;
} Node;

Node tree[1200005];
int a[300005];
int n, m;

void build(int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    tree[p].m = l;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void update(int p, int x) {
    if (tree[p].l == tree[p].r) {
        tree[p].m = x;
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (x <= mid) update(p << 1, x);
    else update(p << 1 | 1, x);
    if (tree[p << 1].m >= tree[p << 1 | 1].m) tree[p].m = tree[p << 1].m;
    else tree[p].m = tree[p << 1 | 1].m;
}

int query(int p, int k) {
    if (tree[p].l == tree[p].r) return tree[p].m;
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (tree[p << 1].m >= k) return query(p << 1, k);
    else return query(p << 1 | 1, k - tree[p << 1].m);
}

int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        update(1, i);
    }
    for (int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", a[query(1, k)]);
    }
    return 0;
}