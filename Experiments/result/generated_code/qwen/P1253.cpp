#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, q;
long long a[MAXN];
long long lazy_update[MAXN];
long long lazy_add[MAXN];

void push_down(int node, int start, int end) {
    if (lazy_update[node] != 0 || lazy_add[node] != 0) {
        int mid = (start + end) / 2;
        if (lazy_update[node] != 0) {
            a[start] = lazy_update[node];
            a[end] = lazy_update[node];
            lazy_update[2 * node] = lazy_update[node];
            lazy_update[2 * node + 1] = lazy_update[node];
        }
        if (lazy_add[node] != 0) {
            a[start] += lazy_add[node];
            a[end] += lazy_add[node];
            lazy_add[2 * node] += lazy_add[node];
            lazy_add[2 * node + 1] += lazy_add[node];
        }
        lazy_update[node] = 0;
        lazy_add[node] = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, long long val) {
    push_down(node, start, end);
    if (r < start || end < l)
        return;
    if (l <= start && end <= r) {
        lazy_update[node] = val;
        push_down(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update_range(2 * node, start, mid, l, r, val);
    update_range(2 * node + 1, mid + 1, end, l, r, val);
    a[node] = a[2 * node] > a[2 * node + 1] ? a[2 * node] : a[2 * node + 1];
}

void add_range(int node, int start, int end, int l, int r, long long val) {
    push_down(node, start, end);
    if (r < start || end < l)
        return;
    if (l <= start && end <= r) {
        lazy_add[node] += val;
        push_down(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    add_range(2 * node, start, mid, l, r, val);
    add_range(2 * node + 1, mid + 1, end, l, r, val);
    a[node] = a[2 * node] > a[2 * node + 1] ? a[2 * node] : a[2 * node + 1];
}

long long query_max(int node, int start, int end, int l, int r) {
    push_down(node, start, end);
    if (r < start || end < l)
        return -1e9;
    if (l <= start && end <= r)
        return a[node];
    int mid = (start + end) / 2;
    long long left_max = query_max(2 * node, start, mid, l, r);
    long long right_max = query_max(2 * node + 1, mid + 1, end, l, r);
    return left_max > right_max ? left_max : right_max;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < q; i++) {
        int op, l, r, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %lld", &l, &r, &x);
            update_range(1, 1, n, l, r, x);
        } else if (op == 2) {
            scanf("%d %d %lld", &l, &r, &x);
            add_range(1, 1, n, l, r, x);
        } else if (op == 3) {
            scanf("%d %d", &l, &r);
            printf("%lld\n", query_max(1, 1, n, l, r));
        }
    }
    return 0;
}