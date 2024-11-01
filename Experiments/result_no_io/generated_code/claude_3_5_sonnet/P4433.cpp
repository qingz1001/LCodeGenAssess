#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define ll long long

ll tree[MAXN * 4], lazy[MAXN * 4];
int n, q;

void pushdown(int node, int l, int r) {
    if (lazy[node] != 0) {
        int mid = (l + r) / 2;
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int L, int R, ll A, ll B) {
    if (L <= l && r <= R) {
        ll sum = ((ll)(r - L + 1) * (r + L) / 2 % B * A % B + B) % B;
        tree[node] += sum;
        lazy[node] += A;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) update(node * 2, l, mid, L, R, A, B);
    if (R > mid) update(node * 2 + 1, mid + 1, r, L, R, A, B);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[node];
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    if (L <= mid) res += query(node * 2, l, mid, L, R);
    if (R > mid) res += query(node * 2 + 1, mid + 1, r, L, R);
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    
    while (q--) {
        int op, L, R;
        scanf("%d %d %d", &op, &L, &R);
        if (op == 1) {
            ll A, B;
            scanf("%lld %lld", &A, &B);
            update(1, 1, n, L, R, A, B);
        } else {
            printf("%lld\n", query(1, 1, n, L, R));
        }
    }
    
    return 0;
}