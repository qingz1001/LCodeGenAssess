#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define ll long long

ll n, p, m;
ll a[MAXN];

struct Node {
    ll sum, add, mul;
} tree[MAXN * 4];

void pushup(ll rt) {
    tree[rt].sum = (tree[rt * 2].sum + tree[rt * 2 + 1].sum) % p;
}

void pushdown(ll rt, ll l, ll r) {
    ll mid = (l + r) >> 1;
    ll lc = rt * 2, rc = rt * 2 + 1;
    
    if (tree[rt].mul != 1) {
        tree[lc].sum = tree[lc].sum * tree[rt].mul % p;
        tree[rc].sum = tree[rc].sum * tree[rt].mul % p;
        tree[lc].mul = tree[lc].mul * tree[rt].mul % p;
        tree[rc].mul = tree[rc].mul * tree[rt].mul % p;
        tree[lc].add = tree[lc].add * tree[rt].mul % p;
        tree[rc].add = tree[rc].add * tree[rt].mul % p;
        tree[rt].mul = 1;
    }
    
    if (tree[rt].add) {
        tree[lc].sum = (tree[lc].sum + tree[rt].add * (mid - l + 1)) % p;
        tree[rc].sum = (tree[rc].sum + tree[rt].add * (r - mid)) % p;
        tree[lc].add = (tree[lc].add + tree[rt].add) % p;
        tree[rc].add = (tree[rc].add + tree[rt].add) % p;
        tree[rt].add = 0;
    }
}

void build(ll rt, ll l, ll r) {
    tree[rt].add = 0;
    tree[rt].mul = 1;
    if (l == r) {
        tree[rt].sum = a[l] % p;
        return;
    }
    ll mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    pushup(rt);
}

void update_mul(ll rt, ll l, ll r, ll L, ll R, ll c) {
    if (L <= l && r <= R) {
        tree[rt].sum = tree[rt].sum * c % p;
        tree[rt].mul = tree[rt].mul * c % p;
        tree[rt].add = tree[rt].add * c % p;
        return;
    }
    pushdown(rt, l, r);
    ll mid = (l + r) >> 1;
    if (L <= mid) update_mul(rt * 2, l, mid, L, R, c);
    if (R > mid) update_mul(rt * 2 + 1, mid + 1, r, L, R, c);
    pushup(rt);
}

void update_add(ll rt, ll l, ll r, ll L, ll R, ll c) {
    if (L <= l && r <= R) {
        tree[rt].sum = (tree[rt].sum + c * (r - l + 1)) % p;
        tree[rt].add = (tree[rt].add + c) % p;
        return;
    }
    pushdown(rt, l, r);
    ll mid = (l + r) >> 1;
    if (L <= mid) update_add(rt * 2, l, mid, L, R, c);
    if (R > mid) update_add(rt * 2 + 1, mid + 1, r, L, R, c);
    pushup(rt);
}

ll query(ll rt, ll l, ll r, ll L, ll R) {
    if (L <= l && r <= R) {
        return tree[rt].sum;
    }
    pushdown(rt, l, r);
    ll mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(rt * 2, l, mid, L, R)) % p;
    if (R > mid) res = (res + query(rt * 2 + 1, mid + 1, r, L, R)) % p;
    return res;
}

int main() {
    scanf("%lld %lld", &n, &p);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    
    scanf("%lld", &m);
    while (m--) {
        ll op, t, g, c;
        scanf("%lld %lld %lld", &op, &t, &g);
        if (op == 1) {
            scanf("%lld", &c);
            update_mul(1, 1, n, t, g, c);
        } else if (op == 2) {
            scanf("%lld", &c);
            update_add(1, 1, n, t, g, c);
        } else {
            printf("%lld\n", query(1, 1, n, t, g));
        }
    }
    
    return 0;
}