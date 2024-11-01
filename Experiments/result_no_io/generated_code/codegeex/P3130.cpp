#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int l, r;
    int min, add;
} Node;

Node tree[800005];
int a[200005];

void build(int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    tree[p].min = 0;
    tree[p].add = 0;
    if (l == r) {
        tree[p].min = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    tree[p].min = tree[p * 2].min < tree[p * 2 + 1].min ? tree[p * 2].min : tree[p * 2 + 1].min;
}

void pushdown(int p) {
    if (tree[p].add == 0) return;
    tree[p * 2].min += tree[p].add;
    tree[p * 2 + 1].min += tree[p].add;
    tree[p * 2].add += tree[p].add;
    tree[p * 2 + 1].add += tree[p].add;
    tree[p].add = 0;
}

void update(int p, int l, int r, int x) {
    if (l <= tree[p].l && tree[p].r <= r) {
        tree[p].min += x;
        tree[p].add += x;
        return;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    if (l <= mid) update(p * 2, l, r, x);
    if (mid < r) update(p * 2 + 1, l, r, x);
    tree[p].min = tree[p * 2].min < tree[p * 2 + 1].min ? tree[p * 2].min : tree[p * 2 + 1].min;
}

int query_min(int p, int l, int r) {
    if (l <= tree[p].l && tree[p].r <= r) {
        return tree[p].min;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    int min = 1000000;
    if (l <= mid) min = min < query_min(p * 2, l, r) ? min : query_min(p * 2, l, r);
    if (mid < r) min = min < query_min(p * 2 + 1, l, r) ? min : query_min(p * 2 + 1, l, r);
    return min;
}

int query_sum(int p, int l, int r) {
    if (l <= tree[p].l && tree[p].r <= r) {
        return (tree[p].r - tree[p].l + 1) * tree[p].min;
    }
    pushdown(p);
    int mid = (tree[p].l + tree[p].r) / 2;
    int sum = 0;
    if (l <= mid) sum += query_sum(p * 2, l, r);
    if (mid < r) sum += query_sum(p * 2 + 1, l, r);
    return sum;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);
    char op;
    int x, y, z;
    for (int i = 0; i < q; i++) {
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &x, &y);
            printf("%d\n", query_min(1, x, y));
        } else if (op == 'S') {
            scanf("%d %d", &x, &y);
            printf("%d\n", query_sum(1, x, y));
        } else if (op == 'P') {
            scanf("%d %d %d", &x, &y, &z);
            update(1, x, y, z);
        }
    }
    return 0;
}