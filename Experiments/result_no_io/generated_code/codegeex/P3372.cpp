#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll segTree[MAXN * 4], lazy[MAXN * 4];

void build(ll* arr, int node, int start, int end) {
    if (start == end) {
        segTree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(arr, node * 2, start, mid);
        build(arr, node * 2 + 1, mid + 1, end);
        segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
    }
}

void updateRange(int node, int start, int end, int l, int r, int val) {
    if (lazy[node] != 0) {
        segTree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r) {
        segTree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node * 2, start, mid, l, r, val);
    updateRange(node * 2 + 1, mid + 1, end, l, r, val);
    segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
}

ll queryRange(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l)
        return 0;
    if (lazy[node] != 0) {
        segTree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start >= l && end <= r)
        return segTree[node];
    int mid = (start + end) / 2;
    ll p1 = queryRange(node * 2, start, mid, l, r);
    ll p2 = queryRange(node * 2 + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    ll arr[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(arr, 1, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y, k;
            scanf("%d %d %d", &x, &y, &k);
            updateRange(1, 0, n - 1, x - 1, y - 1, k);
        } else if (type == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%lld\n", queryRange(1, 0, n - 1, x - 1, y - 1));
        }
    }
    return 0;
}