#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005

typedef long long ll;

typedef struct {
    ll max;
    ll lazy_set;
    ll lazy_add;
    int set_flag;
} Node;

Node tree[4 * MAXN];
ll arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].max = arr[start];
        tree[node].lazy_set = 0;
        tree[node].lazy_add = 0;
        tree[node].set_flag = 0;
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
        tree[node].lazy_set = 0;
        tree[node].lazy_add = 0;
        tree[node].set_flag = 0;
    }
}

void push_down(int node) {
    if (tree[node].set_flag) {
        tree[2 * node].max = tree[node].lazy_set;
        tree[2 * node + 1].max = tree[node].lazy_set;
        tree[2 * node].lazy_set = tree[node].lazy_set;
        tree[2 * node + 1].lazy_set = tree[node].lazy_set;
        tree[2 * node].lazy_add = 0;
        tree[2 * node + 1].lazy_add = 0;
        tree[2 * node].set_flag = 1;
        tree[2 * node + 1].set_flag = 1;
        tree[node].set_flag = 0;
    }
    if (tree[node].lazy_add) {
        tree[2 * node].max += tree[node].lazy_add;
        tree[2 * node + 1].max += tree[node].lazy_add;
        tree[2 * node].lazy_add += tree[node].lazy_add;
        tree[2 * node + 1].lazy_add += tree[node].lazy_add;
        tree[node].lazy_add = 0;
    }
}

void update_set(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].max = val;
        tree[node].lazy_set = val;
        tree[node].lazy_add = 0;
        tree[node].set_flag = 1;
        return;
    }
    push_down(node);
    int mid = (start + end) / 2;
    if (l <= mid) update_set(2 * node, start, mid, l, r, val);
    if (r > mid) update_set(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
}

void update_add(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].max += val;
        tree[node].lazy_add += val;
        return;
    }
    push_down(node);
    int mid = (start + end) / 2;
    if (l <= mid) update_add(2 * node, start, mid, l, r, val);
    if (r > mid) update_add(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max = (tree[2 * node].max > tree[2 * node + 1].max) ? tree[2 * node].max : tree[2 * node + 1].max;
}

ll query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].max;
    }
    push_down(node);
    int mid = (start + end) / 2;
    ll max_left = LLONG_MIN, max_right = LLONG_MIN;
    if (l <= mid) max_left = query(2 * node, start, mid, l, r);
    if (r > mid) max_right = query(2 * node + 1, mid + 1, end, l, r);
    return (max_left > max_right) ? max_left : max_right;
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