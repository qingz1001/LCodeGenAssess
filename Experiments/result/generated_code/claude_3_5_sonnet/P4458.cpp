#include <stdio.h>
#include <string.h>

#define MAXN 200005
#define MOD 1000000007

typedef long long ll;

ll tree[MAXN * 4], lazy[MAXN * 4];
ll a[MAXN], sum[MAXN], sum2[MAXN];
int n, m;

void push_up(int node) {
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        lazy[node * 2] = (lazy[node * 2] + lazy[node]) % MOD;
        lazy[node * 2 + 1] = (lazy[node * 2 + 1] + lazy[node]) % MOD;
        tree[node * 2] = (tree[node * 2] + lazy[node] * (mid - l + 1)) % MOD;
        tree[node * 2 + 1] = (tree[node * 2 + 1] + lazy[node] * (r - mid)) % MOD;
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

void update(int node, int l, int r, int ul, int ur, ll val) {
    if (ul <= l && r <= ur) {
        tree[node] = (tree[node] + val * (r - l + 1)) % MOD;
        lazy[node] = (lazy[node] + val) % MOD;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ul <= mid) update(node * 2, l, mid, ul, ur, val);
    if (ur > mid) update(node * 2 + 1, mid + 1, r, ul, ur, val);
    push_up(node);
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    if (ql <= mid) res = (res + query(node * 2, l, mid, ql, qr)) % MOD;
    if (qr > mid) res = (res + query(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum[i] = (sum[i-1] + a[i]) % MOD;
        sum2[i] = (sum2[i-1] + (ll)i * a[i] % MOD) % MOD;
    }
    build(1, 1, n);
    
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int u, v;
            ll d;
            scanf("%d %d %lld", &u, &v, &d);
            if (u > v) {
                int temp = u;
                u = v;
                v = temp;
            }
            update(1, 1, n, u, v, d);
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            ll res = 0;
            for (int i = l; i <= r; i++) {
                ll len = n - i + 1;
                ll s = query(1, 1, n, 1, len);
                ll s2 = (sum2[len] - sum2[i-1] + MOD) % MOD;
                res = (res + s * len % MOD - s2 + MOD) % MOD;
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}