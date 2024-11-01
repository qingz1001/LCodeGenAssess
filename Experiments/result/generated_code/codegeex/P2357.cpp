#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 200005

ll a[MAXN]; // 存储墓碑风水值
ll tag[MAXN]; // 存储区间加的懒标记
ll sum[MAXN]; // 存储前缀和

// 构建线段树
void build(int l, int r, int x) {
    if (l == r) {
        sum[x] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, x << 1);
    build(m + 1, r, x << 1 | 1);
    sum[x] = sum[x << 1] + sum[x << 1 | 1];
}

// 区间更新
void update(int L, int R, int l, int r, int x, int v) {
    if (L <= l && r <= R) {
        sum[x] += (r - l + 1) * v;
        tag[x] += v;
        return;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, l, m, x << 1, v);
    if (R > m) update(L, R, m + 1, r, x << 1 | 1, v);
    sum[x] = sum[x << 1] + sum[x << 1 | 1] + (r - l + 1) * tag[x];
}

// 区间查询
ll query(int L, int R, int l, int r, int x) {
    if (L <= l && r <= R) {
        return sum[x];
    }
    int m = (l + r) >> 1;
    ll res = 0;
    if (L <= m) res += query(L, R, l, m, x << 1);
    if (R > m) res += query(L, R, m + 1, r, x << 1 | 1);
    return res + (r - l + 1) * tag[x];
}

int main() {
    int n, f;
    scanf("%d%d", &n, &f);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, n, 1);
    while (f--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            update(l, r, 1, n, 1, k);
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            update(1, 1, 1, n, 1, k);
        } else if (op == 3) {
            int k;
            scanf("%d", &k);
            update(1, 1, 1, n, 1, -k);
        } else if (op == 4) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l, r, 1, n, 1));
        } else if (op == 5) {
            printf("%lld\n", query(1, 1, 1, n, 1));
        }
    }
    return 0;
}