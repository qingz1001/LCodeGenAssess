#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 500005
#define MAXM 500005

typedef long long ll;

int n, m, x, y, T;
ll a[MAXN];
ll tree[MAXN << 2], lazy[MAXN << 2];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void pushup(int rt) {
    tree[rt] = gcd(tree[rt << 1], tree[rt << 1 | 1]);
}

void pushdown(int rt, int l, int r) {
    if (lazy[rt]) {
        int mid = (l + r) >> 1;
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        tree[rt << 1] += lazy[rt];
        tree[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        tree[rt] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        tree[rt] += val;
        lazy[rt] += val;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt << 1, l, mid, L, R, val);
    if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R, val);
    pushup(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = query(rt << 1, l, mid, L, R);
    if (R > mid) res = gcd(res, query(rt << 1 | 1, mid + 1, r, L, R));
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d", &x, &y);
    scanf("%d", &T);
    
    for (int i = 1; i <= n * m; i++) {
        scanf("%lld", &a[i]);
    }
    
    build(1, 1, n * m);
    
    while (T--) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int L = (x - x1 - 1) * m + y - y1;
            int R = (x + x2 - 1) * m + y + y2;
            if (L > R) {
                int temp = L;
                L = R;
                R = temp;
            }
            printf("%lld\n", llabs(query(1, 1, n * m, L, R)));
        } else {
            int x1, y1, x2, y2;
            ll c;
            scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &c);
            int L = (x1 - 1) * m + y1;
            int R = x2 * m + y2 - 1;
            update(1, 1, n * m, L, R, c);
        }
    }
    
    return 0;
}