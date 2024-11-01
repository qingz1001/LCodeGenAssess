#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

long long a[MAXN];
long long lazy[MAXN * 4];
long long tree[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        int mid = (start + end) / 2;
        tree[node * 2] += lazy[node] * (mid - start + 1);
        tree[node * 2 + 1] += lazy[node] * (end - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, long long val) {
    if (l > end || r < start) return;
    if (l <= start && end <= r) {
        tree[node] += val * (end - start + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, val);
    update(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int start, int end, int idx) {
    if (start == end) return tree[node];
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (idx <= mid) return query(node * 2, start, mid, idx);
    else return query(node * 2 + 1, mid + 1, end, idx);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    build(1, 1, n);
    
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x;
            long long y;
            scanf("%d %lld", &x, &y);
            for (int j = x; j <= n; j += x) {
                update(1, 1, n, j, j, y);
            }
        } else {
            int j;
            scanf("%d", &j);
            printf("%lld\n", query(1, 1, n, j));
        }
    }
    
    return 0;
}