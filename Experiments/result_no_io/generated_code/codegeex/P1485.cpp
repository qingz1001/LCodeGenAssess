#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n, k;
ll m[500005];
ll sum[500005];
ll left[500005], right[500005];
ll l, r, mid;

bool check(ll p) {
    for (ll i = 1; i <= n; i++) {
        ll damage = p - (i - 1) * (i - 1);
        if (damage < 0) damage = 0;
        m[i] -= damage;
    }
    for (ll i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + m[i];
    }
    ll cnt = 0;
    for (ll i = 1; i <= n; i++) {
        if (sum[i] <= 0) {
            cnt++;
            m[i] = -sum[i];
            sum[i] = 0;
            if (i < n) m[i + 1] += m[i];
        }
    }
    if (cnt > k) return false;
    for (ll i = 1; i <= n; i++) {
        ll damage = p - (n - i) * (n - i);
        if (damage < 0) damage = 0;
        m[i] -= damage;
    }
    for (ll i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + m[i];
    }
    cnt = 0;
    for (ll i = 1; i <= n; i++) {
        if (sum[i] <= 0) {
            cnt++;
            m[i] = -sum[i];
            sum[i] = 0;
            if (i < n) m[i + 1] += m[i];
        }
    }
    return cnt <= k;
}

int main() {
    scanf("%lld %lld", &n, &k);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &m[i]);
    }
    l = 1;
    r = 10000000000;
    while (l < r) {
        mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%lld\n", l);
    return 0;
}