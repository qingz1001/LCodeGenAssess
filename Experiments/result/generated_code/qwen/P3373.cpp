#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int val, lazy_mul, lazy_add;
} Node;

Node tree[MAXN * 4];
int arr[MAXN];

void push_down(int node, int left, int right) {
    if (tree[node].lazy_mul != 1 || tree[node].lazy_add != 0) {
        tree[node * 2].val = (long long)tree[node * 2].val * tree[node].lazy_mul + (right - left + 1) * tree[node].lazy_add % tree[node].lazy_mul;
        tree[node * 2].lazy_mul = (long long)tree[node * 2].lazy_mul * tree[node].lazy_mul % tree[node].lazy_mul;
        tree[node * 2].lazy_add = (long long)tree[node * 2].lazy_add * tree[node].lazy_mul + tree[node].lazy_add % tree[node].lazy_mul;

        tree[node * 2 + 1].val = (long long)tree[node * 2 + 1].val * tree[node].lazy_mul + (right - left + 1) * tree[node].lazy_add % tree[node].lazy_mul;
        tree[node * 2 + 1].lazy_mul = (long long)tree[node * 2 + 1].lazy_mul * tree[node].lazy_mul % tree[node].lazy_mul;
        tree[node * 2 + 1].lazy_add = (long long)tree[node * 2 + 1].lazy_add * tree[node].lazy_mul + tree[node].lazy_add % tree[node].lazy_mul;

        tree[node].lazy_mul = 1;
        tree[node].lazy_add = 0;
    }
}

void build_tree(int node, int left, int right) {
    if (left == right) {
        tree[node].val = arr[left];
        tree[node].lazy_mul = 1;
        tree[node].lazy_add = 0;
    } else {
        int mid = (left + right) / 2;
        build_tree(node * 2, left, mid);
        build_tree(node * 2 + 1, mid + 1, right);
        tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % tree[node].lazy_mul;
    }
}

void update_range_mul(int node, int left, int right, int start, int end, int mul) {
    if (start <= left && right <= end) {
        tree[node].val = (long long)tree[node].val * mul % tree[node].lazy_mul;
        tree[node].lazy_mul = (long long)tree[node].lazy_mul * mul % tree[node].lazy_mul;
        tree[node].lazy_add = (long long)tree[node].lazy_add * mul % tree[node].lazy_mul;
    } else {
        push_down(node, left, right);
        int mid = (left + right) / 2;
        if (start <= mid) update_range_mul(node * 2, left, mid, start, end, mul);
        if (end > mid) update_range_mul(node * 2 + 1, mid + 1, right, start, end, mul);
        tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % tree[node].lazy_mul;
    }
}

void update_range_add(int node, int left, int right, int start, int end, int add) {
    if (start <= left && right <= end) {
        tree[node].val = (tree[node].val + (right - left + 1) * add) % tree[node].lazy_mul;
        tree[node].lazy_add = (tree[node].lazy_add + add) % tree[node].lazy_mul;
    } else {
        push_down(node, left, right);
        int mid = (left + right) / 2;
        if (start <= mid) update_range_add(node * 2, left, mid, start, end, add);
        if (end > mid) update_range_add(node * 2 + 1, mid + 1, right, start, end, add);
        tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % tree[node].lazy_mul;
    }
}

int query_range_sum(int node, int left, int right, int start, int end) {
    if (start <= left && right <= end) return tree[node].val;
    push_down(node, left, right);
    int mid = (left + right) / 2, res = 0;
    if (start <= mid) res += query_range_sum(node * 2, left, mid, start, end);
    if (end > mid) res += query_range_sum(node * 2 + 1, mid + 1, right, start, end);
    return res % tree[node].lazy_mul;
}

int main() {
    int n, q, m;
    scanf("%d %d %d", &n, &q, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    build_tree(1, 1, n);

    while (q--) {
        int op, x, y, k;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            scanf("%d", &k);
            update_range_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            scanf("%d", &k);
            update_range_add(1, 1, n, x, y, k);
        } else {
            printf("%d\n", query_range_sum(1, 1, n, x, y));
        }
    }

    return 0;
}