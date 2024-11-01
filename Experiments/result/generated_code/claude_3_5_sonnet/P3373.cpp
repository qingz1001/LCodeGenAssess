#include <stdio.h>
#define MAXN 100005
#define ll long long

ll n, q, m, a[MAXN];
ll sum[MAXN * 4], add[MAXN * 4], mul[MAXN * 4];

void pushup(int rt) {
    sum[rt] = (sum[rt * 2] + sum[rt * 2 + 1]) % m;
}

void pushdown(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    if (mul[rt] != 1) {
        mul[rt * 2] = mul[rt * 2] * mul[rt] % m;
        mul[rt * 2 + 1] = mul[rt * 2 + 1] * mul[rt] % m;
        add[rt * 2] = add[rt * 2] * mul[rt] % m;
        add[rt * 2 + 1] = add[rt * 2 + 1] * mul[rt] % m;
        sum[rt * 2] = sum[rt * 2] * mul[rt] % m;
        sum[rt * 2 + 1] = sum[rt * 2 + 1] * mul[rt] % m;
        mul[rt] = 1;
    }
    if (add[rt]) {
        add[rt * 2] = (add[rt * 2] + add[rt]) % m;
        add[rt * 2 + 1] = (add[rt * 2 + 1] + add[rt]) % m;
        sum[rt * 2] = (sum[rt * 2] + add[rt] * (mid - l + 1)) % m;
        sum[rt * 2 + 1] = (sum[rt * 2 + 1] + add[rt] * (r - mid)) % m;
        add[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    mul[rt] = 1;
    if (l == r) {
        sum[rt] = a[l] % m;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    pushup(rt);
}

void update_mul(int rt, int l, int r, int L, int R, ll k) {
    if (L <= l && r <= R) {
        mul[rt] = mul[rt] * k % m;
        add[rt] = add[rt] * k % m;
        sum[rt] = sum[rt] * k % m;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_mul(rt * 2, l, mid, L, R, k);
    if (R > mid) update_mul(rt * 2 + 1, mid + 1, r, L, R, k);
    pushup(rt);
}

void update_add(int rt, int l, int r, int L, int R, ll k) {
    if (L <= l && r <= R) {
        add[rt] = (add[rt] + k) % m;
        sum[rt] = (sum[rt] + k * (r - l + 1)) % m;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update_add(rt * 2, l, mid, L, R, k);
    if (R > mid) update_add(rt * 2 + 1, mid + 1, r, L, R, k);
    pushup(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(rt * 2, l, mid, L, R)) % m;
    if (R > mid) res = (res + query(rt * 2 + 1, mid + 1, r, L, R)) % m;
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