#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

int n, m;
ll tree[MAXN * 4], lazy[MAXN * 4];
ll sum[MAXN], sqsum[MAXN];

void pushup(int node) {
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void pushdown(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        tree[node] += val * (r - l + 1);
        lazy[node] += val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
    pushup(node);
}

ll query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    if (ql <= mid) res += query(node * 2, l, mid, ql, qr);
    if (qr > mid) res += query(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i-1] + i;
        sqsum[i] = sqsum[i-1] + (ll)i * i;
    }
    
    char op[2];
    int l, r, v;
    for (int i = 0; i < m; i++) {
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d%d%d", &l, &r, &v);
            update(1, 1, n-1, l, r-1, v);
        } else {
            scanf("%d%d", &l, &r);
            ll total = query(1, 1, n-1, l, r-1);
            ll cnt = r - l + 1;
            ll numerator = total * cnt - (sum[r-l] - sum[0]);
            ll denominator = cnt * (cnt - 1) / 2;
            ll g = gcd(numerator, denominator);
            printf("%lld/%lld\n", numerator / g, denominator / g);
        }
    }
    
    return 0;
}