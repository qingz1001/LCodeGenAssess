#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 500005
#define MOD 1000000007

typedef long long ll;

ll a[MAXN], s[MAXN], pre[MAXN], sum[MAXN], q[MAXN];
int n, m;

void add(int l, int r, ll d) {
    pre[l] += d;
    pre[r + 1] -= d;
    sum[l] += d * (ll)(l - 1) * (l - 2) / 2 + d * (ll)(l - 1) * r;
    sum[r + 1] -= d * (ll)(r) * (r + 1) * (r + 2) / 6 - d * (ll)r * (r + 1) / 2;
}

ll query(int l, int r) {
    ll res = 0;
    res += (s[r] - s[l - 1]) * (ll)(l + r) * (l - r + 1) / 2;
    res += (pre[l] + pre[r + 1]) * (ll)(l + r) * (l - r + 1) / 2;
    res += (sum[r + 1] - sum[l - 1]);
    return res % MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        s[i] = (s[i - 1] + a[i]) % MOD;
    }

    for (int i = 1; i <= m; i++) {
        int op, l, r;
        ll d;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%lld", &l, &r, &d);
            add(l, r, d);
        } else {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l, r));
        }
    }

    return 0;
}