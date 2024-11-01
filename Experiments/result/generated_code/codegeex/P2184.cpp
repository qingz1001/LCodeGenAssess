#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int tree[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = 0;
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] += val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

int query(int node, int start, int end, int L, int R) {
    if (R < start || end < L) {
        return 0;
    }
    if (L <= start && end <= R) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, L, R) + query(2 * node + 1, mid + 1, end, L, R);
}

int main() {
    scanf("%d %d", &n, &m);
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int q, l, r;
        scanf("%d %d %d", &q, &l, &r);
        if (q == 1) {
            update(1, 1, n, l, 1);
            update(1, 1, n, r + 1, -1);
        } else if (q == 2) {
            printf("%d\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}