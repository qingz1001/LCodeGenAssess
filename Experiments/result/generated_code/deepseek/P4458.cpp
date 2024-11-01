#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 200005

typedef long long ll;

ll a[MAXN], sum[MAXN], sum2[MAXN];

void update(int u, int v, int d, int n) {
    if (u > v) {
        int temp = u;
        u = v;
        v = temp;
    }
    sum[u] = (sum[u] + d) % MOD;
    if (v + 1 <= n) sum[v + 1] = (sum[v + 1] - d + MOD) % MOD;
}

void build_prefix_sum(int n) {
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i] + sum[i - 1]) % MOD;
        a[i] = (a[i] + sum[i]) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        sum2[i] = (sum2[i - 1] + a[i]) % MOD;
    }
}

ll query(int l, int r, int n) {
    ll res = 0;
    for (int i = l; i <= r; i++) {
        res = (res + (sum2[n - i + 1] - sum2[i - 1] + MOD) % MOD) % MOD;
    }
    return res;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int u, v, d;
            scanf("%d %d %d", &u, &v, &d);
            update(u, v, d, n);
        } else if (type == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            build_prefix_sum(n);
            printf("%lld\n", query(l, r, n));
        }
    }

    return 0;
}