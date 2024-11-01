#include <stdio.h>

#define MAXN 100005

long long tree[MAXN * 4]; // 线段树数组
long long lazy[MAXN * 4]; // 懒惰标记数组

// 构建线段树
void build(int node, int start, int end, long long arr[]) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// 更新线段树
void update(int node, int start, int end, int l, int r, long long val) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// 查询线段树
long long query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l)
        return 0;
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start >= l && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    long long p1 = query(2 * node, start, mid, l, r);
    long long p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long arr[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 0, n - 1, arr);
    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y;
            long long k;
            scanf("%d %d %lld", &x, &y, &k);
            update(1, 0, n - 1, x - 1, y - 1, k);
        } else if (type == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%lld\n", query(1, 0, n - 1, x - 1, y - 1));
        }
    }
    return 0;
}