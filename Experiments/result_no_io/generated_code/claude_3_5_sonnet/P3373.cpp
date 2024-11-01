#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define ll long long

ll n, q, m, a[MAXN];
ll sum[MAXN<<2], add[MAXN<<2], mul[MAXN<<2];

void pushup(int rt) {
    sum[rt] = (sum[rt<<1] + sum[rt<<1|1]) % m;
}

void pushdown(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    ll lc = rt << 1, rc = rt << 1 | 1;
    
    mul[lc] = mul[lc] * mul[rt] % m;
    mul[rc] = mul[rc] * mul[rt] % m;
    add[lc] = (add[lc] * mul[rt] + add[rt]) % m;
    add[rc] = (add[rc] * mul[rt] + add[rt]) % m;
    
    sum[lc] = (sum[lc] * mul[rt] + add[rt] * (mid - l + 1)) % m;
    sum[rc] = (sum[rc] * mul[rt] + add[rt] * (r - mid)) % m;
    
    mul[rt] = 1;
    add[rt] = 0;
}

void build(int rt, int l, int r) {
    mul[rt] = 1;
    add[rt] = 0;
    if (l == r) {
        sum[rt] = a[l] % m;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}

void update_mul(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        mul[rt] = mul[rt] * val % m;
        add[rt] = add[rt] * val % m;
        sum[rt] = sum[rt] * val % m;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_mul(rt<<1, l, mid, L, R, val);
    if (R > mid) update_mul(rt<<1|1, mid+1, r, L, R, val);
    pushup(rt);
}

void update_add(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        add[rt] = (add[rt] + val) % m;
        sum[rt] = (sum[rt] + val * (r - l + 1)) % m;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_add(rt<<1, l, mid, L, R, val);
    if (R > mid) update_add(rt<<1|1, mid+1, r, L, R, val);
    pushup(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(rt<<1, l, mid, L, R)) % m;
    if (R > mid) res = (res + query(rt<<1|1, mid+1, r, L, R)) % m;
    return res;
}

int main() {
    scanf("%lld%lld%lld", &n, &q, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    
    build(1, 1, n);
    
    while (q--) {
        int op, x, y;
        ll k;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            scanf("%lld", &k);
            update_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            scanf("%lld", &k);
            update_add(1, 1, n, x, y, k);
        } else {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    
    return 0;
}