#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005

typedef long long ll;

typedef struct {
    ll max;
    ll lazy_set;
    ll lazy_add;
} Node;

Node tree[4 * MAXN];
ll arr[MAXN];

void push_down(int node, int start, int end) {
    if (tree[node].lazy_set != LLONG_MIN) {
        tree[node].max = tree[node].lazy_set;
        if (start != end) {
            tree[2 * node].lazy_set = tree[node].lazy_set;
            tree[2 * node + 1].lazy_set = tree[node].lazy_set;
            tree[2 * node].lazy_add = 0;
            tree[2 * node + 1].lazy_add = 0;
        }
        tree[node].lazy_set = LLONG_MIN;
    }
    if (tree[node].lazy_add != 0) {
        tree[node].max += tree[node].lazy_add;
        if (start != end) {
            if (tree[2 * node].lazy_set != LLONG_MIN) {
                tree[2 * node].lazy_set += tree[node].lazy_add;
            } else {
                tree[2 * node].lazy_add += tree[node].lazy_add;
            }
            if (tree[2 * node + 1].lazy_set != LLONG_MIN) {
                tree[2 * node + 1].lazy_set += tree[node].lazy_add;
            } else {
                tree[2 * node + 1].lazy_add += tree[node].lazy_add;
            }
        }
        tree[node].lazy_add = 0;
    }
}

void build(int node, int start, int end) {
    tree[node].lazy_set = LLONG_MIN;
    tree[node].lazy_add = 0;
    if (start == end) {
        tree[node].max = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
    }
}

void update_set(int node, int start, int end, int l, int r, ll val) {
    push_down(node, start, end);
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        tree[node].lazy_set = val;
        tree[node].lazy_add = 0;
        push_down(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update_set(2 * node, start, mid, l, r, val);
    update_set(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
}

void update_add(int node, int start, int end, int l, int r, ll val) {
    push_down(node, start, end);
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        tree[node].lazy_add += val;
        push_down(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update_add(2 * node, start, mid, l, r, val);
    update_add(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
}

ll query(int node, int start, int end, int l, int r) {
    push_down(node, start, end);
    if (start > r || end < l) return LLONG_MIN;
    if (start >= l && end <= r) return tree[node].max;
    int mid = (start + end) / 2;
    ll left = query(2 * node, start, mid, l, r);
    ll right = query(2 * node + 1, mid + 1, end, l, r);
    return (left > right) ? left : right;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, n);
    while (q--) {
        int op, l, r;
        ll x;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf("%lld", &x);
            update_set(1, 1, n, l, r, x);
        } else if (op == 2) {
            scanf("%lld", &x);
            update_add(1, 1, n, l, r, x);
        } else if (op == 3) {
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}