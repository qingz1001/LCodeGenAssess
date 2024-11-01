#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXC 1000005

int n, m;
int a[MAXN];
int cnt[MAXC];
int tree[MAXN << 2][MAXC];

void pushup(int node, int color) {
    tree[node][color] = tree[node << 1][color] + tree[node << 1 | 1][color];
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node][a[l]] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    for (int i = 1; i <= cnt[0]; i++) {
        pushup(node, cnt[i]);
    }
}

void update(int node, int l, int r, int pos, int oldcolor, int newcolor) {
    if (l == r) {
        tree[node][oldcolor] = 0;
        tree[node][newcolor] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(node << 1, l, mid, pos, oldcolor, newcolor);
    else update(node << 1 | 1, mid + 1, r, pos, oldcolor, newcolor);
    pushup(node, oldcolor);
    pushup(node, newcolor);
}

int query(int node, int l, int r, int ql, int qr, int color) {
    if (ql <= l && r <= qr) return tree[node][color];
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(node << 1, l, mid, ql, qr, color);
    if (qr > mid) res += query(node << 1 | 1, mid + 1, r, ql, qr, color);
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (!cnt[a[i]]) cnt[++cnt[0]] = a[i];
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
            update(1, 1, n, x, a[x], a[x + 1]);
            update(1, 1, n, x + 1, a[x + 1], a[x]);
            int temp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = temp;
        }
    }
    return 0;
}