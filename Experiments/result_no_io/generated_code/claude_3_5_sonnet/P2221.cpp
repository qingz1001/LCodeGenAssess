#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

int n, m;
ll tree[MAXN << 2], lazy[MAXN << 2];
ll sum[MAXN], cnt[MAXN];

void push_up(int rt) {
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void push_down(int rt, int l, int r) {
    if (lazy[rt]) {
        int mid = (l + r) >> 1;
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        tree[rt << 1] += lazy[rt] * (mid - l + 1);
        tree[rt << 1 | 1] += lazy[rt] * (r - mid);
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    lazy[rt] = 0;
    if (l == r) {
        tree[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    push_up(rt);
}

void update(int rt, int l, int r, int L, int R, ll v) {
    if (L <= l && r <= R) {
        lazy[rt] += v;
        tree[rt] += v * (r - l + 1);
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt << 1, l, mid, L, R, v);
    if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R, v);
    push_up(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res += query(rt << 1, l, mid, L, R);
    if (R > mid) res += query(rt << 1 | 1, mid + 1, r, L, R);
    return res;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    scanf("%d%d", &n, &m);
    build(1, 1, n - 1);
    
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + i - 1;
        cnt[i] = cnt[i-1] + i;
    }
    
    char op[2];
    int l, r;
    ll v;
    
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d%d%lld", &l, &r, &v);
            update(1, 1, n - 1, l, r - 1, v);
        } else {
            scanf("%d%d", &l, &r);
            ll total = query(1, 1, n - 1, l, r - 1);
            ll pairs = (ll)(r - l + 1) * (r - l) / 2;
            ll numerator = total * (r - l + 1) - 2 * (sum[r] - sum[l-1]);
            ll denominator = pairs;
            ll g = gcd(numerator, denominator);
            printf("%lld/%lld\n", numerator / g, denominator / g);
        }
    }
    
    return 0;
}