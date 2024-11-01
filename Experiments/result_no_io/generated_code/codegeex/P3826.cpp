#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define N 100005

struct Vegetable {
    ll a, s, c, x;
} v[N];

ll n, m, k, p[N], f[N], g[N];

int main() {
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &v[i].a, &v[i].s, &v[i].c, &v[i].x);
    }
    for (int i = 1; i <= k; i++) {
        scanf("%lld", &p[i]);
    }

    for (int i = 1; i <= k; i++) {
        ll ans = 0;
        for (int j = 1; j <= n; j++) {
            ll remaining = m;
            for (int d = 1; d <= p[i]; d++) {
                ll变质量 = (d - 1) * v[j].x;
                if (变质量 >= v[j].c) {
                    break;
                }
                ll可销售量 = v[j].c - 变质量;
                if (可销售量 > remaining) {
                    可销售量 = remaining;
                }
                ans += 可销售量 * v[j].a;
                if (d == 1) {
                    ans += 可销售量 * v[j].s;
                }
                remaining -= 可销售量;
                if (remaining == 0) {
                    break;
                }
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}