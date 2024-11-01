#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

int a[MAXN];
int tree[MAXN * 4];

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(node * 2, start, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, end, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 0;
    if (l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
}

void modifyRange(int n, int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        update(1, 1, n, i, x++);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    buildTree(1, 1, n);

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            modifyRange(n, l, r, x);
        } else {
            printf("%d\n", query(1, 1, n, 1, n));
        }
    }

    return 0;
}