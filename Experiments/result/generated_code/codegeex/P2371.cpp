#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll n, l, r, a[13], f[5000005];

ll min(ll x, ll y) {
    return x < y ? x : y;
}

ll max(ll x, ll y) {
    return x > y ? x : y;
}

void solve() {
    scanf("%lld%lld%lld", &n, &l, &r);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 计算最大公约数
    ll g = a[1];
    for (int i = 2; i <= n; i++) {
        g = __gcd(g, a[i]);
    }

    // 如果最大公约数不为1，则无解
    if (g != 1) {
        printf("0\n");
        return;
    }

    // 计算f数组
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= 5000000; j++) {
            f[j] |= f[j - a[i]];
        }
    }

    // 计算满足条件的b的数量
    ll ans = 0;
    for (ll i = l; i <= r; i++) {
        if (f[i % a[1]]) {
            ans++;
        }
    }
    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}