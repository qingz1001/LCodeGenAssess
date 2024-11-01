#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXM 100000

typedef struct {
    int l, r;
    long long val, add, mul;
} Node;

Node tree[4 * MAXN];
long long a[MAXN];

void build(int node, int start, int end) {
    tree[node].l = start;
    tree[node].r = end;
    tree[node].val = 0;
    tree[node].add = 0;
    tree[node].mul = 1;
    if (start == end) {
        tree[node].val = a[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].val = (tree[2 * node].val + tree[2 * node + 1].val) % 1000000007;
    }
}

void updateRangeAdd(int node, int start, int end, long long value) {
    if (tree[node].l > end || tree[node].r < start) return;
    if (tree[node].l >= start && tree[node].r <= end) {
        tree[node].val = (tree[node].val + (tree[node].r - tree[node].l + 1) * value) % 1000000007;
        tree[node].add = (tree[node].add + value) % 1000000007;
        return;
    }
    updateRangeAdd(2 * node, start, end, value);
    updateRangeAdd(2 * node + 1, start, end, value);
    tree[node].val = (tree[2 * node].val + tree[2 * node + 1].val) % 1000000007;
}

void updateRangeMul(int node, int start, int end, long long value) {
    if (tree[node].l > end || tree[node].r < start) return;
    if (tree[node].l >= start && tree[node].r <= end) {
        tree[node].val = (tree[node].val * value) % 1000000007;
        tree[node].add = (tree[node].add * value) % 1000000007;
        tree[node].mul = (tree[node].mul * value) % 1000000007;
        return;
    }
    updateRangeMul(2 * node, start, end, value);
    updateRangeMul(2 * node + 1, start, end, value);
    tree[node].val = (tree[2 * node].val + tree[2 * node + 1].val) % 1000000007;
}

long long queryRange(int node, int start, int end) {
    if (tree[node].l > end || tree[node].r < start) return 0;
    if (tree[node].l >= start && tree[node].r <= end) {
        return tree[node].val;
    }
    long long p1 = queryRange(2 * node, start, end);
    long long p2 = queryRange(2 * node + 1, start, end);
    return (p1 + p2) % 1000000007;
}

int main() {
    int n, p, m;
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 0, n - 1);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int t, g;
            long long c;
            scanf("%d %d %lld", &t, &g, &c);
            updateRangeMul(1, t - 1, g - 1, c);
        } else if (op == 2) {
            int t, g;
            long long c;
            scanf("%d %d %lld", &t, &g, &c);
            updateRangeAdd(1, t - 1, g - 1, c);
        } else if (op == 3) {
            int t, g;
            scanf("%d %d", &t, &g);
            printf("%lld\n", queryRange(1, t - 1, g - 1) % 1000000007);
        }
    }
    return 0;
}