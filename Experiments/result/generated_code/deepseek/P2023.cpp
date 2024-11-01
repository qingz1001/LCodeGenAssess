#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll arr[MAXN];
ll sum[MAXN << 2];
ll lazy_add[MAXN << 2];
ll lazy_mul[MAXN << 2];
ll mod;

void build(int node, int start, int end) {
    lazy_add[node] = 0;
    lazy_mul[node] = 1;
    if (start == end) {
        sum[node] = arr[start];
    } else {
        int mid = (start + end) >> 1;
        build(node << 1, start, mid);
        build(node << 1 | 1, mid + 1, end);
        sum[node] = (sum[node << 1] + sum[node << 1 | 1]) % mod;
    }
}

void push_down(int node, int start, int end) {
    if (lazy_mul[node] != 1) {
        sum[node << 1] = sum[node << 1] * lazy_mul[node] % mod;
        sum[node << 1 | 1] = sum[node << 1 | 1] * lazy_mul[node] % mod;
        lazy_mul[node << 1] = lazy_mul[node << 1] * lazy_mul[node] % mod;
        lazy_mul[node << 1 | 1] = lazy_mul[node << 1 | 1] * lazy_mul[node] % mod;
        lazy_add[node << 1] = lazy_add[node << 1] * lazy_mul[node] % mod;
        lazy_add[node << 1 | 1] = lazy_add[node << 1 | 1] * lazy_mul[node] % mod;
        lazy_mul[node] = 1;
    }
    if (lazy_add[node] != 0) {
        int mid = (start + end) >> 1;
        sum[node << 1] = (sum[node << 1] + lazy_add[node] * (mid - start + 1)) % mod;
        sum[node << 1 | 1] = (sum[node << 1 | 1] + lazy_add[node] * (end - mid)) % mod;
        lazy_add[node << 1] = (lazy_add[node << 1] + lazy_add[node]) % mod;
        lazy_add[node << 1 | 1] = (lazy_add[node << 1 | 1] + lazy_add[node]) % mod;
        lazy_add[node] = 0;
    }
}

void update_mul(int node, int start, int end, int l, int r, ll c) {
    if (l <= start && end <= r) {
        sum[node] = sum[node] * c % mod;
        lazy_mul[node] = lazy_mul[node] * c % mod;
        lazy_add[node] = lazy_add[node] * c % mod;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    if (l <= mid) update_mul(node << 1, start, mid, l, r, c);
    if (r > mid) update_mul(node << 1 | 1, mid + 1, end, l, r, c);
    sum[node] = (sum[node << 1] + sum[node << 1 | 1]) % mod;
}

void update_add(int node, int start, int end, int l, int r, ll c) {
    if (l <= start && end <= r) {
        sum[node] = (sum[node] + c * (end - start + 1)) % mod;
        lazy_add[node] = (lazy_add[node] + c) % mod;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    if (l <= mid) update_add(node << 1, start, mid, l, r, c);
    if (r > mid) update_add(node << 1 | 1, mid + 1, end, l, r, c);
    sum[node] = (sum[node << 1] + sum[node << 1 | 1]) % mod;
}

ll query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return sum[node];
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    ll res = 0;
    if (l <= mid) res = (res + query(node << 1, start, mid, l, r)) % mod;
    if (r > mid) res = (res + query(node << 1 | 1, mid + 1, end, l, r)) % mod;
    return res;
}

int main() {
    int n, m;
    scanf("%d %lld", &n, &mod);
    for (int i = 1; i <= n; i++) scanf("%lld", &arr[i]);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        int op, t, g;
        ll c;
        scanf("%d %d %d", &op, &t, &g);
        if (op == 1) {
            scanf("%lld", &c);
            update_mul(1, 1, n, t, g, c);
        } else if (op == 2) {
            scanf("%lld", &c);
            update_add(1, 1, n, t, g, c);
        } else if (op == 3) {
            printf("%lld\n", query(1, 1, n, t, g));
        }
    }
    return 0;
}