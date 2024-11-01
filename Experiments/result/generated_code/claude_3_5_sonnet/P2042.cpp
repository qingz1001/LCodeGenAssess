#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 500005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, m;
int a[MAXN];

struct Node {
    int l, r;
    ll sum, lmax, rmax, max;
} tree[MAXN * 4];

void pushup(int p) {
    tree[p].sum = tree[p*2].sum + tree[p*2+1].sum;
    tree[p].lmax = (tree[p*2].lmax > tree[p*2].sum + tree[p*2+1].lmax) ? tree[p*2].lmax : tree[p*2].sum + tree[p*2+1].lmax;
    tree[p].rmax = (tree[p*2+1].rmax > tree[p*2+1].sum + tree[p*2].rmax) ? tree[p*2+1].rmax : tree[p*2+1].sum + tree[p*2].rmax;
    tree[p].max = (tree[p*2].max > tree[p*2+1].max) ? tree[p*2].max : tree[p*2+1].max;
    tree[p].max = (tree[p].max > tree[p*2].rmax + tree[p*2+1].lmax) ? tree[p].max : tree[p*2].rmax + tree[p*2+1].lmax;
}

void build(int p, int l, int r) {
    tree[p].l = l;
    tree[p].r = r;
    if (l == r) {
        tree[p].sum = tree[p].lmax = tree[p].rmax = tree[p].max = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p*2, l, mid);
    build(p*2+1, mid+1, r);
    pushup(p);
}

void update(int p, int x, int v) {
    if (tree[p].l == tree[p].r) {
        tree[p].sum = tree[p].lmax = tree[p].rmax = tree[p].max = v;
        return;
    }
    int mid = (tree[p].l + tree[p].r) / 2;
    if (x <= mid) update(p*2, x, v);
    else update(p*2+1, x, v);
    pushup(p);
}

Node query(int p, int l, int r) {
    if (l <= tree[p].l && tree[p].r <= r) return tree[p];
    int mid = (tree[p].l + tree[p].r) / 2;
    if (r <= mid) return query(p*2, l, r);
    if (l > mid) return query(p*2+1, l, r);
    Node left = query(p*2, l, r);
    Node right = query(p*2+1, l, r);
    Node res;
    res.sum = left.sum + right.sum;
    res.lmax = (left.lmax > left.sum + right.lmax) ? left.lmax : left.sum + right.lmax;
    res.rmax = (right.rmax > right.sum + left.rmax) ? right.rmax : right.sum + left.rmax;
    res.max = (left.max > right.max) ? left.max : right.max;
    res.max = (res.max > left.rmax + right.lmax) ? res.max : left.rmax + right.lmax;
    return res;
}

void insert(int pos, int tot) {
    for (int i = n; i > pos; i--) {
        a[i+tot] = a[i];
    }
    for (int i = 1; i <= tot; i++) {
        scanf("%d", &a[pos+i]);
    }
    n += tot;
    build(1, 1, n);
}

void delete(int pos, int tot) {
    for (int i = pos+tot; i <= n; i++) {
        a[i-tot] = a[i];
    }
    n -= tot;
    build(1, 1, n);
}

void make_same(int pos, int tot, int c) {
    for (int i = pos; i < pos+tot; i++) {
        update(1, i, c);
    }
}

void reverse(int pos, int tot) {
    for (int i = 0; i < tot/2; i++) {
        int temp = a[pos+i];
        a[pos+i] = a[pos+tot-1-i];
        a[pos+tot-1-i] = temp;
    }
    build(1, 1, n);
}

ll get_sum(int pos, int tot) {
    return query(1, pos, pos+tot-1).sum;
}

ll max_sum() {
    return query(1, 1, n).max;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);

    char op[20];
    int pos, tot, c;
    for (int i = 0; i < m; i++) {
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d%d", &pos, &tot);
            insert(pos, tot);
        } else if (strcmp(op, "DELETE") == 0) {
            scanf("%d%d", &pos, &tot);
            delete(pos, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            scanf("%d%d%d", &pos, &tot, &c);
            make_same(pos, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            scanf("%d%d", &pos, &tot);
            reverse(pos, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            scanf("%d%d", &pos, &tot);
            printf("%lld\n", get_sum(pos, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%lld\n", max_sum());
        }
    }

    return 0;
}