#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll tree[MAXN * 4];
ll lazy[MAXN * 4];
ll arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        int mid = (start + end) / 2;
        tree[node * 2] += lazy[node] * (mid - start + 1);
        tree[node * 2 + 1] += lazy[node] * (end - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node] += val * (end - start + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update(node * 2, start, mid, l, r, val);
    if (r > mid) update(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    ll sum = 0;
    if (l <= mid) sum += query(node * 2, start, mid, l, r);
    if (r > mid) sum += query(node * 2 + 1, mid + 1, end, l, r);
    return sum;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int type, x, y;
        ll k;
        scanf("%d %d %d", &type, &x, &y);
        if (type == 1) {
            scanf("%lld", &k);
            update(1, 1, n, x, y, k);
        } else {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}