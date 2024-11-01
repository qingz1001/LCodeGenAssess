#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ll;

ll a[400005], b[400005], c[400005], d[400005];
ll n, k, l, r, mid, ans, cnt;
ll stk[400005], top;

void solve() {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    ll l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] > mid) {
                c[i] = 1;
            } else {
                c[i] = 0;
            }
        }
        ll s = 0;
        for (int i = 1; i <= n; i++) {
            if (c[i] == 1) {
                s++;
            } else {
                d[i] = s;
                s = 0;
            }
        }
        ll sum = 0, pos = 0;
        for (int i = 1; i <= n; i++) {
            if (c[i] == 0) {
                sum++;
            } else {
                if (sum > 0) {
                    if (d[i] + sum - 1 >= k) {
                        pos = i;
                        break;
                    }
                    sum = 0;
                }
            }
        }
        if (pos == 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%lld", ans);
}

int main() {
    solve();
    return 0;
}