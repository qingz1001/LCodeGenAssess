#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 400005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, q;
ll a[N], sum[N], add[N];
int L[N], R[N], bel[N];
ll mx[N], pre[N], suf[N], tag[N];
int block, num;

void build() {
    block = sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= n; i++) {
        bel[i] = (i - 1) / block + 1;
        if (L[bel[i]] == 0) L[bel[i]] = i;
        R[bel[i]] = i;
    }
}

void init() {
    for (int i = 1; i <= num; i++) {
        ll now = 0;
        mx[i] = pre[i] = suf[i] = -INF;
        for (int j = L[i]; j <= R[i]; j++) {
            sum[j] = sum[j-1] + a[j];
            now += a[j];
            mx[i] = (mx[i] > now) ? mx[i] : now;
            pre[i] = (pre[i] > sum[j] - sum[L[i]-1]) ? pre[i] : (sum[j] - sum[L[i]-1]);
            suf[i] = (suf[i] > sum[R[i]] - sum[j-1]) ? suf[i] : (sum[R[i]] - sum[j-1]);
            if (now < 0) now = 0;
        }
    }
}

void update(int x, ll v) {
    int b = bel[x];
    add[x] += v;
    ll now = 0;
    mx[b] = pre[b] = suf[b] = -INF;
    for (int i = L[b]; i <= R[b]; i++) {
        now += a[i] + add[i];
        mx[b] = (mx[b] > now) ? mx[b] : now;
        pre[b] = (pre[b] > now) ? pre[b] : now;
        suf[b] = (suf[b] > sum[R[b]] - sum[i-1] + now - (sum[i] - sum[L[b]-1])) ? suf[b] : (sum[R[b]] - sum[i-1] + now - (sum[i] - sum[L[b]-1]));
        if (now < 0) now = 0;
    }
}

void modify(int l, int r, ll x) {
    int bl = bel[l], br = bel[r];
    if (bl == br) {
        for (int i = l; i <= r; i++) update(i, x);
    } else {
        for (int i = l; i <= R[bl]; i++) update(i, x);
        for (int i = bl + 1; i < br; i++) tag[i] += x;
        for (int i = L[br]; i <= r; i++) update(i, x);
    }
}

ll query(int l, int r) {
    int bl = bel[l], br = bel[r];
    ll res = 0, now = 0;
    if (bl == br) {
        for (int i = l; i <= r; i++) {
            now += a[i] + add[i] + tag[bl];
            res = (res > now) ? res : now;
            if (now < 0) now = 0;
        }
    } else {
        for (int i = l; i <= R[bl]; i++) {
            now += a[i] + add[i] + tag[bl];
            res = (res > now) ? res : now;
            if (now < 0) now = 0;
        }
        ll tmp = now;
        for (int i = bl + 1; i < br; i++) {
            ll cur = (mx[i] > 0) ? mx[i] : 0;
            res = (res > tmp + pre[i] + tag[i] * (R[i] - L[i] + 1)) ? res : (tmp + pre[i] + tag[i] * (R[i] - L[i] + 1));
            tmp += suf[i] + tag[i] * (R[i] - L[i] + 1);
            res = (res > tmp) ? res : tmp;
            tmp = (tmp > cur) ? tmp : cur;
        }
        now = tmp;
        for (int i = L[br]; i <= r; i++) {
            now += a[i] + add[i] + tag[br];
            res = (res > now) ? res : now;
            if (now < 0) now = 0;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build();
    init();
    while (q--) {
        int op, l, r;
        ll x;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%lld", &x);
            modify(l, r, x);
        } else {
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}