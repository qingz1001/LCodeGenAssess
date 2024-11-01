#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stdlib.h>
#define mp make_pair
#define pb push_back
#define re register
#define ll long long
#define il inline
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int inf=1e9;
const int N=1e5+100;
const int M=1e5+100;
const double eps=1e-8;
const int mod=1e9+7;

int n, m;
int a[N], tag[N];

struct node {
    int l, r, val, lz;
} tree[N << 2];

#define ls (rt << 1)
#define rs (rt << 1 | 1)

il void pushup(int rt) {
    tree[rt].val = max(tree[ls].val, tree[rs].val);
}

il void pushdown(int rt) {
    if (tree[rt].lz) {
        tree[ls].val = max(tree[ls].val, tree[rt].lz);
        tree[rs].val = max(tree[rs].val, tree[rt].lz);
        tree[ls].lz = max(tree[ls].lz, tree[rt].lz);
        tree[rs].lz = max(tree[rs].lz, tree[rt].lz);
        tree[rt].lz = 0;
    }
}

void build(int rt, int l, int r) {
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].lz = 0;
    if (l == r) {
        tree[rt].val = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int val) {
    if (l <= tree[rt].l && tree[rt].r <= r) {
        tree[rt].val = max(tree[rt].val, val);
        tree[rt].lz = max(tree[rt].lz, val);
        return;
    }
    pushdown(rt);
    int mid = (tree[rt].l + tree[rt].r) >> 1;
    if (l <= mid) update(ls, l, r, val);
    if (r > mid) update(rs, l, r, val);
    pushup(rt);
}

int query(int rt, int l, int r) {
    if (l <= tree[rt].l && tree[rt].r <= r) {
        return tree[rt].val;
    }
    pushdown(rt);
    int mid = (tree[rt].l + tree[rt].r) >> 1;
    int res = -inf;
    if (l <= mid) res = max(res, query(ls, l, r));
    if (r > mid) res = max(res, query(rs, l, r));
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--) {
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            scanf("%d", &x);
            update(1, l, r, x);
        } else {
            printf("%d\n", query(1, l, r));
        }
    }
    return 0;
}