#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 571373

typedef long long ll;

ll tree[MAXN * 4];
ll lazy_add[MAXN * 4];
ll lazy_mul[MAXN * 4];
ll arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
    }
    lazy_add[node] = 0;
    lazy_mul[node] = 1;
}

void push_down(int node, int start, int end) {
    if (lazy_mul[node] != 1) {
        tree[node * 2] = (tree[node * 2] * lazy_mul[node]) % MOD;
        tree[node * 2 + 1] = (tree[node * 2 + 1] * lazy_mul[node]) % MOD;
        lazy_mul[node * 2] = (lazy_mul[node * 2] * lazy_mul[node]) % MOD;
        lazy_mul[node * 2 + 1] = (lazy_mul[node * 2 + 1] * lazy_mul[node]) % MOD;
        lazy_add[node * 2] = (lazy_add[node * 2] * lazy_mul[node]) % MOD;
        lazy_add[node * 2 + 1] = (lazy_add[node * 2 + 1] * lazy_mul[node]) % MOD;
        lazy_mul[node] = 1;
    }
    if (lazy_add[node] != 0) {
        int mid = (start + end) / 2;
        tree[node * 2] = (tree[node * 2] + lazy_add[node] * (mid - start + 1)) % MOD;
        tree[node * 2 + 1] = (tree[node * 2 + 1] + lazy_add[node] * (end - mid)) % MOD;
        lazy_add[node * 2] = (lazy_add[node * 2] + lazy_add[node]) % MOD;
        lazy_add[node * 2 + 1] = (lazy_add[node * 2 + 1] + lazy_add[node]) % MOD;
        lazy_add[node] = 0;
    }
}

void update_mul(int node, int start, int end, int l, int r, ll val) {
    if (r < start || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        tree[node] = (tree[node] * val) % MOD;
        lazy_mul[node] = (lazy_mul[node] * val) % MOD;
        lazy_add[node] = (lazy_add[node] * val) % MOD;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    update_mul(node * 2, start, mid, l, r, val);
    update_mul(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

void update_add(int node, int start, int end, int l, int r, ll val) {
    if (r < start || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        tree[node] = (tree[node] + val * (end - start + 1)) % MOD;
        lazy_add[node] = (lazy_add[node] + val) % MOD;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    update_add(node * 2, start, mid, l, r, val);
    update_add(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    ll p1 = query(node * 2, start, mid, l, r);
    ll p2 = query(node * 2 + 1, mid + 1, end, l, r);
    return (p1 + p2) % MOD;
}

int main() {
    int n, q, m;
    scanf("%d %d %d", &n, &q, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, n);
    while (q--) {
        int type, x, y;
        ll k;
        scanf("%d %d %d", &type, &x, &y);
        if (type == 1) {
            scanf("%lld", &k);
            update_mul(1, 1, n, x, y, k);
        } else if (type == 2) {
            scanf("%lld", &k);
            update_add(1, 1, n, x, y, k);
        } else if (type == 3) {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}