#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000
#define MAX_Q 100000

int n, q;
int haybales[MAX_N];
int tree[MAX_N * 4];

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = haybales[start];
    } else {
        int mid = (start + end) / 2;
        build_tree(node * 2, start, mid);
        build_tree(node * 2 + 1, mid + 1, end);
        tree[node] = fmin(tree[node * 2], tree[node * 2 + 1]);
    }
}

void update_tree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] += val;
        haybales[idx] += val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update_tree(node * 2, start, mid, idx, val);
        } else {
            update_tree(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = fmin(tree[node * 2], tree[node * 2 + 1]);
    }
}

int query_min(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MAX;
    } else if (l <= start && end <= r) {
        return tree[node];
    } else {
        int mid = (start + end) / 2;
        int left = query_min(node * 2, start, mid, l, r);
        int right = query_min(node * 2 + 1, mid + 1, end, l, r);
        return fmin(left, right);
    }
}

long long query_sum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    } else if (l <= start && end <= r) {
        return tree[node] * (end - start + 1);
    } else {
        int mid = (start + end) / 2;
        long long left = query_sum(node * 2, start, mid, l, r);
        long long right = query_sum(node * 2 + 1, mid + 1, end, l, r);
        return left + right;
    }
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &haybales[i]);
    }

    build_tree(1, 0, n - 1);

    char op;
    int a, b, c;
    while (q--) {
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query_min(1, 0, n - 1, a - 1, b - 1));
        } else if (op == 'P') {
            scanf("%d %d %d", &a, &b, &c);
            for (int i = a - 1; i < b; i++) {
                update_tree(1, 0, n - 1, i, c);
            }
        } else if (op == 'S') {
            scanf("%d %d", &a, &b);
            printf("%lld\n", query_sum(1, 0, n - 1, a - 1, b - 1));
        }
    }

    return 0;
}