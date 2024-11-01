#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

int n, m;
long long arr[MAXN];
long long tree[MAXM * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        arr[idx] += val;
        tree[node] += val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(node * 2, start, mid, idx, val);
        } else {
            update(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

long long query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    } else if (l <= start && end <= r) {
        return tree[node];
    } else {
        int mid = (start + end) / 2;
        return query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y, k;
            scanf("%d %d %d", &x, &y, &k);
            update(1, 0, n - 1, x - 1, k);
        } else if (type == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%lld\n", query(1, 0, n - 1, x - 1, y - 1));
        }
    }
    return 0;
}