#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll tree[4 * MAXN];
ll lazy[4 * MAXN];

void build(int node, int start, int end, ll arr[]) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update_lazy(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, ll val) {
    update_lazy(node, start, end);
    if (start > end || start > r || end < l) return;
    if (start >= l && end <= r) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

ll query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return 0;
    update_lazy(node, start, end);
    if (start >= l && end <= r) return tree[node];
    int mid = (start + end) / 2;
    ll p1 = query(2 * node, start, mid, l, r);
    ll p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    ll arr[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, n, arr);
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