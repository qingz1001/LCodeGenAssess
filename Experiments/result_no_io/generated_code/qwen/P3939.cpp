#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 10005

int a[MAXN];
int tree[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = (a[start] != 0);
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
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

int query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            int count = 0;
            for (int j = l; j <= r; j++) {
                if (a[j] == c) {
                    count++;
                }
            }
            printf("%d\n", count);
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            int temp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = temp;
            update(1, 1, n, x, (a[x] != 0));
            update(1, 1, n, x + 1, (a[x + 1] != 0));
        }
    }

    return 0;
}