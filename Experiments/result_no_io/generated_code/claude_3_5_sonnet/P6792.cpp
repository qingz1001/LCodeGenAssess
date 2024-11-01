#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100005
#define MAX_Q 200005
#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef long long ll;

ll a[MAX_N];
int n, q;

struct Node {
    ll sum, pre, suf, ans;
} tree[MAX_N << 2];

void pushup(int rt) {
    tree[rt].sum = tree[LEFT(rt)].sum + tree[RIGHT(rt)].sum;
    tree[rt].pre = max(tree[LEFT(rt)].pre, tree[LEFT(rt)].sum + tree[RIGHT(rt)].pre);
    tree[rt].suf = max(tree[RIGHT(rt)].suf, tree[RIGHT(rt)].sum + tree[LEFT(rt)].suf);
    tree[rt].ans = max(max(tree[LEFT(rt)].ans, tree[RIGHT(rt)].ans), tree[LEFT(rt)].suf + tree[RIGHT(rt)].pre);
}

void build(int rt, int l, int r) {
    if (l == r) {
        tree[rt].sum = tree[rt].pre = tree[rt].suf = tree[rt].ans = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(LEFT(rt), l, mid);
    build(RIGHT(rt), mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, ll x) {
    if (L <= l && r <= R) {
        if (tree[rt].sum >= (r - l + 1) * x) return;
        if (tree[rt].pre == tree[rt].sum && tree[rt].suf == tree[rt].sum && tree[rt].ans == tree[rt].sum) {
            tree[rt].sum = tree[rt].pre = tree[rt].suf = tree[rt].ans = (r - l + 1) * x;
            return;
        }
    }
    if (l == r) {
        tree[rt].sum = tree[rt].pre = tree[rt].suf = tree[rt].ans = max(tree[rt].sum, x);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) update(LEFT(rt), l, mid, L, R, x);
    if (R > mid) update(RIGHT(rt), mid + 1, r, L, R, x);
    pushup(rt);
}

Node query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(LEFT(rt), l, mid, L, R);
    if (L > mid) return query(RIGHT(rt), mid + 1, r, L, R);
    Node left = query(LEFT(rt), l, mid, L, R);
    Node right = query(RIGHT(rt), mid + 1, r, L, R);
    Node res;
    res.sum = left.sum + right.sum;
    res.pre = max(left.pre, left.sum + right.pre);
    res.suf = max(right.suf, right.sum + left.suf);
    res.ans = max(max(left.ans, right.ans), left.suf + right.pre);
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            ll x;
            scanf("%lld", &x);
            update(1, 1, n, l, r, x);
        } else {
            printf("%lld\n", max(0LL, query(1, 1, n, l, r).ans));
        }
    }
    return 0;
}