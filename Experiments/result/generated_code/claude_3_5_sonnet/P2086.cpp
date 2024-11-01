#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXM 500005

typedef long long ll;

int n, m, x, y, T;
ll a[MAXN][MAXM];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

struct SegmentTree {
    ll gcd[MAXN * 4], lazy[MAXN * 4];
    
    void pushup(int rt) {
        gcd[rt] = gcd(gcd[rt * 2], gcd[rt * 2 + 1]);
    }
    
    void pushdown(int rt, int l, int r) {
        if (lazy[rt]) {
            int mid = (l + r) >> 1;
            lazy[rt * 2] += lazy[rt];
            lazy[rt * 2 + 1] += lazy[rt];
            gcd[rt * 2] += lazy[rt];
            gcd[rt * 2 + 1] += lazy[rt];
            lazy[rt] = 0;
        }
    }
    
    void build(int rt, int l, int r, int row) {
        if (l == r) {
            gcd[rt] = a[row][l];
            return;
        }
        int mid = (l + r) >> 1;
        build(rt * 2, l, mid, row);
        build(rt * 2 + 1, mid + 1, r, row);
        pushup(rt);
    }
    
    void update(int rt, int l, int r, int L, int R, ll val) {
        if (L <= l && r <= R) {
            gcd[rt] += val;
            lazy[rt] += val;
            return;
        }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) update(rt * 2, l, mid, L, R, val);
        if (R > mid) update(rt * 2 + 1, mid + 1, r, L, R, val);
        pushup(rt);
    }
    
    ll query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return gcd[rt];
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        ll res = 0;
        if (L <= mid) res = query(rt * 2, l, mid, L, R);
        if (R > mid) res = gcd(res, query(rt * 2 + 1, mid + 1, r, L, R));
        return res;
    }
} seg[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d", &x, &y);
    scanf("%d", &T);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
        seg[i].build(1, 1, m, i);
    }
    
    while (T--) {
        int op, x1, y1, x2, y2;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int xl = x - x1, xr = x + x2;
            int yl = y - y1, yr = y + y2;
            xl = xl < 1 ? 1 : xl;
            xr = xr > n ? n : xr;
            yl = yl < 1 ? 1 : yl;
            yr = yr > m ? m : yr;
            ll res = 0;
            for (int i = xl; i <= xr; i++) {
                res = gcd(res, seg[i].query(1, 1, m, yl, yr));
            }
            printf("%lld\n", res);
        } else {
            ll c;
            scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &c);
            for (int i = x1; i <= x2; i++) {
                seg[i].update(1, 1, m, y1, y2, c);
            }
        }
    }
    
    return 0;
}