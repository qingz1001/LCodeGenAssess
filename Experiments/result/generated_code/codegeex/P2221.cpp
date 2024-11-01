#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100010
#define MAX 100010

typedef long long ll;

ll n, m;
ll a[N], sum[N], cnt[N];
ll lazy[N], tag[N];

void build() {
    for (ll i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        cnt[i] = cnt[i - 1] + i;
    }
}

void push_down(ll o, ll l, ll r) {
    if (lazy[o] || tag[o]) {
        ll mid = (l + r) >> 1;
        ll lc = o << 1, rc = lc | 1;
        ll v = lazy[o], w = tag[o];
        lazy[lc] += v;
        tag[lc] += v * (mid - l + 1);
        lazy[rc] += v;
        tag[rc] += v * (r - mid);
        sum[lc] += tag[lc];
        sum[rc] += tag[rc];
        lazy[o] = 0;
        tag[o] = 0;
    }
}

void update(ll o, ll l, ll r, ll ql, ll qr, ll v) {
    if (ql <= l && r <= qr) {
        lazy[o] += v;
        tag[o] += v * (r - l + 1);
        sum[o] += tag[o];
        return;
    }
    push_down(o, l, r);
    ll mid = (l + r) >> 1;
    ll lc = o << 1, rc = lc | 1;
    if (ql <= mid) update(lc, l, mid, ql, qr, v);
    if (qr > mid) update(rc, mid + 1, r, ql, qr, v);
    sum[o] = sum[lc] + sum[rc];
}

ll query(ll o, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
        return sum[o];
    }
    push_down(o, l, r);
    ll mid = (l + r) >> 1;
    ll lc = o << 1, rc = lc | 1;
    ll ret = 0;
    if (ql <= mid) ret += query(lc, l, mid, ql, qr);
    if (qr > mid) ret += query(rc, mid + 1, r, ql, qr);
    return ret;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (ll i = 1; i <= n; i++) {
        a[i] = 0;
    }
    build();
    while (m--) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'C') {
            ll l, r, v;
            scanf("%lld %lld %lld", &l, &r, &v);
            update(1, 1, n, l, r - 1, v);
        } else {
            ll l, r;
            scanf("%lld %lld", &l, &r);
            ll ans = query(1, 1, n, l, r);
            ll up = ans * (r - l + 1) * (r - l) / 2;
            ll down = (cnt[r] - cnt[l - 1]) * (r - l + 1) - ans;
            ll g = gcd(up, down);
            printf("%lld/%lld\n", up / g, down / g);
        }
    }
    return 0;
}