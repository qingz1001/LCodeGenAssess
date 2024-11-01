#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 300005

int n, q;
long long s[MAXN];
long long lazy[MAXN];

void push_down(int node, int left, int right) {
    if (lazy[node] != 0) {
        s[left] += lazy[node];
        s[right] += lazy[node];
        if (left < right) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int node, int left, int right, int l, int r, long long d) {
    if (l <= left && right <= r) {
        s[node] += d;
        if (left < right) {
            lazy[node * 2] += d;
            lazy[node * 2 + 1] += d;
        }
        return;
    }
    push_down(node, left, right);
    int mid = (left + right) / 2;
    if (l <= mid) update_range(node * 2, left, mid, l, r, d);
    if (r > mid) update_range(node * 2 + 1, mid + 1, right, l, r, d);
    s[node] = s[node * 2] + s[node * 2 + 1];
}

int query_min_suffix_start(int node, int left, int right, int l, int r) {
    if (l <= left && right <= r) {
        int min_pos = left;
        for (int i = left; i <= right; i++) {
            if (s[i] < s[min_pos]) {
                min_pos = i;
            }
        }
        return min_pos;
    }
    push_down(node, left, right);
    int mid = (left + right) / 2;
    int min_pos_left = INT_MAX, min_pos_right = INT_MAX;
    if (l <= mid) min_pos_left = query_min_suffix_start(node * 2, left, mid, l, r);
    if (r > mid) min_pos_right = query_min_suffix_start(node * 2 + 1, mid + 1, right, l, r);
    if (min_pos_left == INT_MAX) return min_pos_right;
    if (min_pos_right == INT_MAX) return min_pos_left;
    return s[min_pos_left] < s[min_pos_right] ? min_pos_left : min_pos_right;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &s[i]);
    }

    for (int i = 1; i <= q; i++) {
        int type, l, r, d;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &l, &r, &d);
            update_range(1, 1, n, l, r, d);
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            printf("%d\n", query_min_suffix_start(1, 1, n, l, r));
        }
    }

    return 0;
}