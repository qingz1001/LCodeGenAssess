#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int tree[MAXN * 4];
int lazy[MAXN * 4];

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        tree[node * 2] ^= (mid - l + 1) & 1;
        tree[node * 2 + 1] ^= (r - mid) & 1;
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        tree[node] ^= (r - l + 1) & 1;
        lazy[node] ^= 1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    push_down(node, l, r);
    int mid = (l + r) / 2, res = 0;
    if (ql <= mid) res += query(node * 2, l, mid, ql, qr);
    if (qr > mid) res += query(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    
    for (int i = 0; i < m; i++) {
        int op, s, e;
        scanf("%d %d %d", &op, &s, &e);
        if (op == 0) {
            update(1, 1, n, s, e);
        } else {
            printf("%d\n", query(1, 1, n, s, e));
        }
    }
    
    return 0;
}