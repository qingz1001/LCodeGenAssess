#include <stdio.h>
#include <string.h>
#define MAXN 200005
#define INF 0x3f3f3f3f

typedef long long ll;

ll tree[MAXN << 2], lazy[MAXN << 2], a[MAXN];
int n, q;

void pushup(int rt) {
    tree[rt] = tree[rt << 1] < tree[rt << 1 | 1] ? tree[rt << 1] : tree[rt << 1 | 1];
}

void pushdown(int rt, int l, int r) {
    if (lazy[rt]) {
        int mid = (l + r) >> 1;
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        tree[rt << 1] += lazy[rt];
        tree[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        tree[rt] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        tree[rt] += val;
        lazy[rt] += val;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt << 1, l, mid, L, R, val);
    if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R, val);
    pushup(rt);
}

ll query_min(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = INF;
    if (L <= mid) res = query_min(rt << 1, l, mid, L, R);
    if (R > mid) res = res < query_min(rt << 1 | 1, mid + 1, r, L, R) ? res : query_min(rt << 1 | 1, mid + 1, r, L, R);
    return res;
}

ll query_sum(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt] * (r - l + 1) + lazy[rt] * (r - l + 1);
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res += query_sum(rt << 1, l, mid, L, R);
    if (R > mid) res += query_sum(rt << 1 | 1, mid + 1, r, L, R);
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    
    char op[2];
    int l, r, x;
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'M') {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query_min(1, 1, n, l, r));
        } else if (op[0] == 'P') {
            scanf("%d%d%d", &l, &r, &x);
            update(1, 1, n, l, r, x);
        } else {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query_sum(1, 1, n, l, r));
        }
    }
    return 0;
}