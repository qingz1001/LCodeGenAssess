#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 400005
#define MAXM 400005

typedef long long ll;

ll a[MAXN], sum[MAXN], tag[MAXN], mx[MAXN], lmx[MAXN], rmx[MAXN];

// 构建线段树
void build(int l, int r, int k) {
    if (l == r) {
        mx[k] = lmx[k] = rmx[k] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, k * 2);
    build(m + 1, r, k * 2 + 1);
    mx[k] = max(lmx[k * 2] + rmx[k * 2 + 1], max(mx[k * 2], mx[k * 2 + 1]));
    lmx[k] = max(lmx[k * 2], sum[m] + lmx[k * 2 + 1]);
    rmx[k] = max(rmx[k * 2 + 1], sum[r] + rmx[k * 2]);
}

// 更新线段树
void update(int l, int r, int k, int ql, int qr, ll x) {
    if (ql <= l && r <= qr) {
        tag[k] += x;
        sum[k] += (r - l + 1) * x;
        mx[k] += (r - l + 1) * x;
        lmx[k] += (r - l + 1) * x;
        rmx[k] += (r - l + 1) * x;
        return;
    }
    int m = (l + r) / 2;
    if (tag[k]) {
        if (ql <= m) update(l, m, k * 2, ql, qr, tag[k]);
        if (qr > m) update(m + 1, r, k * 2 + 1, ql, qr, tag[k]);
        tag[k] = 0;
    }
    if (ql <= m) update(l, m, k * 2, ql, qr, x);
    if (qr > m) update(m + 1, r, k * 2 + 1, ql, qr, x);
    mx[k] = max(lmx[k * 2] + rmx[k * 2 + 1], max(mx[k * 2], mx[k * 2 + 1]));
    lmx[k] = max(lmx[k * 2], sum[m] + lmx[k * 2 + 1]);
    rmx[k] = max(rmx[k * 2 + 1], sum[r] + rmx[k * 2]);
}

// 查询线段树
ll query(int l, int r, int k, int ql, int qr) {
    if (ql <= l && r <= qr) return mx[k];
    int m = (l + r) / 2;
    ll res = 0;
    if (tag[k]) {
        if (ql <= m) res = max(res, query(l, m, k * 2, ql, qr) + (ql <= l ? tag[k] * (m - l + 1) : 0));
        if (qr > m) res = max(res, query(m + 1, r, k * 2 + 1, ql, qr) + (qr > m ? tag[k] * (r - m) : 0));
        return res;
    }
    if (ql <= m) res = max(res, query(l, m, k * 2, ql, qr));
    if (qr > m) res = max(res, query(m + 1, r, k * 2 + 1, ql, qr));
    return res;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
    build(1, n, 1);
    while (q--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            ll x;
            scanf("%lld", &x);
            update(1, n, 1, l, r, x);
        } else {
            printf("%lld\n", query(1, n, 1, l, r));
        }
    }
    return 0;
}