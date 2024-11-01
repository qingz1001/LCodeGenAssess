#include <stdio.h>
#include <string.h>

#define MAX_N 200005
#define MOD 1000000007

typedef long long ll;

int n, m;
ll a[MAX_N], sum[MAX_N], sum2[MAX_N];
ll lazy[MAX_N << 2], tree[MAX_N << 2], tree2[MAX_N << 2];

void pushup(int node) {
    tree[node] = (tree[node << 1] + tree[node << 1 | 1]) % MOD;
    tree2[node] = (tree2[node << 1] + tree2[node << 1 | 1]) % MOD;
}

void pushdown(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) >> 1;
        ll lz = lazy[node];
        lazy[node << 1] = (lazy[node << 1] + lz) % MOD;
        lazy[node << 1 | 1] = (lazy[node << 1 | 1] + lz) % MOD;
        tree[node << 1] = (tree[node << 1] + lz * (mid - l + 1)) % MOD;
        tree[node << 1 | 1] = (tree[node << 1 | 1] + lz * (r - mid)) % MOD;
        tree2[node << 1] = (tree2[node << 1] + 2 * lz * sum[mid] - lz * lz * (mid - l + 1) % MOD + MOD) % MOD;
        tree2[node << 1 | 1] = (tree2[node << 1 | 1] + 2 * lz * (sum[r] - sum[mid]) - lz * lz * (r - mid) % MOD + MOD) % MOD;
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        tree2[node] = a[l] * a[l] % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    pushup(node);
}

void update(int node, int l, int r, int L, int R, int d) {
    if (L <= l && r <= R) {
        lazy[node] = (lazy[node] + d) % MOD;
        tree[node] = (tree[node] + (ll)d * (r - l + 1)) % MOD;
        tree2[node] = (tree2[node] + 2LL * d * (sum[r] - sum[l - 1]) + (ll)d * d % MOD * (r - l + 1)) % MOD;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(node << 1, l, mid, L, R, d);
    if (R > mid) update(node << 1 | 1, mid + 1, r, L, R, d);
    pushup(node);
}

ll query(int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query(node << 1, l, mid, L, R)) % MOD;
    if (R > mid) res = (res + query(node << 1 | 1, mid + 1, r, L, R)) % MOD;
    return res;
}

ll query2(int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree2[node];
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res = (res + query2(node << 1, l, mid, L, R)) % MOD;
    if (R > mid) res = (res + query2(node << 1 | 1, mid + 1, r, L, R)) % MOD;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum[i] = (sum[i - 1] + a[i]) % MOD;
    }
    build(1, 1, n);

    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            if (u > v) {
                int tmp = u;
                u = v;
                v = tmp;
            }
            update(1, 1, n, u, v, d);
        } else {
            int l, r;
            scanf("%lld%lld", &l, &r);
            ll ans = 0;
            for (int i = l; i <= r; i++) {
                ll s = query(1, 1, n, 1, n - i + 1);
                ll s2 = query2(1, 1, n, 1, n - i + 1);
                ans = (ans + s2 * (n - i + 1) - s * s % MOD + MOD) % MOD;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}