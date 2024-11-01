#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200010
#define INF 0x3f3f3f3f

typedef struct {
    int value;
    int lazy;
} Node;

Node tree[MAXN << 2];

void push_down(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        int mid = (start + end) >> 1;
        tree[node << 1].value += tree[node].lazy * (mid - start + 1);
        tree[node << 1].lazy += tree[node].lazy;
        tree[node << 1 | 1].value += tree[node].lazy * (end - mid);
        tree[node << 1 | 1].lazy += tree[node].lazy;
        tree[node].lazy = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int d) {
    if (l <= start && end <= r) {
        tree[node].value += d * (end - start + 1);
        tree[node].lazy += d;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    if (l <= mid) update_range(node << 1, start, mid, l, r, d);
    if (r > mid) update_range(node << 1 | 1, mid + 1, end, l, r, d);
    tree[node].value = fmin(tree[node << 1].value, tree[node << 1 | 1].value);
}

int query_min_suffix_start(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return start;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1, ans = INF;
    if (l <= mid) ans = fmin(ans, query_min_suffix_start(node << 1, start, mid, l, r));
    if (r > mid) ans = fmin(ans, query_min_suffix_start(node << 1 | 1, mid + 1, end, l, r));
    return ans;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tree[i].value);
    }

    while (q--) {
        int op, l, r, d;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %d", &l, &r, &d);
            update_range(1, 1, n, l, r, d);
        } else {
            scanf("%d %d", &l, &r);
            printf("%d\n", query_min_suffix_start(1, 1, n, l, r));
        }
    }

    return 0;
}