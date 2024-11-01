#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int n, m;
int a[MAXN];
int tree[MAXN * 4][105];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node][a[start]] = 1;
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    for (int i = 1; i <= 100; i++) {
        tree[node][i] = tree[node * 2][i] + tree[node * 2 + 1][i];
    }
}

void update(int node, int start, int end, int idx, int val, int oldval) {
    if (start == end) {
        tree[node][oldval]--;
        tree[node][val]++;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(node * 2, start, mid, idx, val, oldval);
    } else {
        update(node * 2 + 1, mid + 1, end, idx, val, oldval);
    }
    tree[node][oldval]--;
    tree[node][val]++;
}

int query(int node, int start, int end, int l, int r, int color) {
    if (l > end || r < start) return 0;
    if (l <= start && end <= r) return tree[node][color];
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, l, r, color) + query(node * 2 + 1, mid + 1, end, l, r, color);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);
    
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            printf("%d\n", query(1, 1, n, l, r, c));
        } else {
            int x;
            scanf("%d", &x);
            int temp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = temp;
            update(1, 1, n, x, a[x], temp);
            update(1, 1, n, x + 1, a[x + 1], a[x]);
        }
    }
    
    return 0;
}