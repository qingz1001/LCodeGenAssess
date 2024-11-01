#include <stdio.h>

#define mod 1000000007

typedef long long ll;

ll n, m, a[200010], sum[200010], sum2[200010], sum3[200010], add[200010], sum4[200010], sum5[200010];

void update(ll l, ll r, ll d) {
    ll len = r - l + 1;
    add[l] += d;
    add[r + 1] -= d;
    sum[l] += d * len;
    sum[r + 1] -= d * len;
    sum2[l] += d * len * (len + 1) / 2;
    sum2[r + 1] -= d * len * (len + 1) / 2;
    sum3[l] += d * len * (len + 1) * (2 * len + 1) / 6;
    sum3[r + 1] -= d * len * (len + 1) * (2 * len + 1) / 6;
    sum4[l] += d * len * len * (len + 1) * (len + 2) / 24;
    sum4[r + 1] -= d * len * len * (len + 1) * (len + 2) / 24;
    sum5[l] += d * len * len * len * (len + 1) / 6;
    sum5[r + 1] -= d * len * len * len * (len + 1) / 6;
}

ll query(ll l, ll r) {
    ll len = r - l + 1, res = 0;
    res = (sum[l] + sum[r + 1] + sum2[l] + sum2[r + 1] + sum3[l] + sum3[r + 1] + sum4[l] + sum4[r + 1] + sum5[l] + sum5[r + 1]) % mod;
    for (ll i = l; i <= r; i++) {
        res = (res + add[i] * len) % mod;
        len--;
    }
    return res;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        update(i, i, a[i]);
    }
    for (ll i = 1; i <= m; i++) {
        ll opt, l, r, d;
        scanf("%lld%lld%lld", &opt, &l, &r);
        if (opt == 1) {
            scanf("%lld", &d);
            update(l, r, d);
        } else {
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}