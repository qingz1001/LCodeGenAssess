#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int arr[MAXN];
int lazy[MAXN * 4];

void push_down(int node, int start, int end) {
    if (lazy[node]) {
        int mid = (start + end) / 2;
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
        arr[node * 2] = mid - start + 1 - arr[node * 2];
        arr[node * 2 + 1] = end - mid - arr[node * 2 + 1];
        lazy[node] = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        arr[node] = (end - start + 1) * val;
        if (val == 0 || val == 1) {
            lazy[node] = 0;
        } else {
            lazy[node] = 1;
        }
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    update_range(node * 2, start, mid, l, r, val);
    update_range(node * 2 + 1, mid + 1, end, l, r, val);
    arr[node] = arr[node * 2] + arr[node * 2 + 1];
}

int query_sum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return arr[node];
    push_down(node, start, end);
    int mid = (start + end) / 2;
    return query_sum(node * 2, start, mid, l, r) + query_sum(node * 2 + 1, mid + 1, end, l, r);
}

int query_max_consecutive_ones(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) {
        return arr[node];
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    int left = query_max_consecutive_ones(node * 2, start, mid, l, r);
    int right = query_max_consecutive_ones(node * 2 + 1, mid + 1, end, l, r);
    int cross = 0;
    if (mid >= l && r >= mid + 1) {
        int left_end = arr[node * 2];
        int right_start = arr[node * 2 + 1];
        cross = left_end + right_start;
    }
    return cross > left ? (cross > right ? cross : right) : (left > right ? left : right);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0 || op == 1) {
            update_range(1, 0, n - 1, l, r, op);
        } else if (op == 2) {
            update_range(1, 0, n - 1, l, r, 3);
        } else if (op == 3) {
            printf("%d\n", query_sum(1, 0, n - 1, l, r));
        } else if (op == 4) {
            printf("%d\n", query_max_consecutive_ones(1, 0, n - 1, l, r));
        }
    }
    return 0;
}