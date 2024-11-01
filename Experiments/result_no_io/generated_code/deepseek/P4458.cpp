#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 200000
#define MAXM 500000

typedef long long ll;

ll a[MAXN + 1];
ll sum[MAXN + 1];
ll sum2[MAXN + 1];

void update(int u, int v, int d) {
    if (u > v) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = u; i <= v; i++) {
        a[i] = (a[i] + d) % MOD;
    }
    for (int i = 1; i <= MAXN; i++) {
        sum[i] = (sum[i - 1] + a[i]) % MOD;
        sum2[i] = (sum2[i - 1] + sum[i]) % MOD;
    }
}

ll query(int l, int r) {
    if (l > r) {
        int temp = l;
        l = r;
        r = temp;
    }
    ll result = (sum2[r] - sum2[l - 1] + MOD) % MOD;
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + a[i]) % MOD;
        sum2[i] = (sum2[i - 1] + sum[i]) % MOD;
    }

    for (int i = 0; i < m; i++) {
        int type, u, v, d, l, r;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &u, &v, &d);
            update(u, v, d);
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r));
        }
    }

    return 0;
}