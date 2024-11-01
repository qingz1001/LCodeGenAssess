#include <stdio.h>
#include <string.h>

#define MAXN 100005

int n, m;
int tree[MAXN * 4];
int lazy[MAXN * 4];

void pushdown(int node, int start, int end) {
    if (lazy[node]) {
        int mid = (start + end) / 2;
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
        tree[node * 2] = (mid - start + 1) - tree[node * 2];
        tree[node * 2 + 1] = (end - mid) - tree[node * 2 + 1];
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        tree[node] = (end - start + 1) - tree[node];
        lazy[node] ^= 1;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update(node * 2, start, mid, l, r);
    if (r > mid) update(node * 2 + 1, mid + 1, end, l, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int idx) {
    if (start == end) return tree[node];
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (idx <= mid) return query(node * 2, start, mid, idx);
    else return query(node * 2 + 1, mid + 1, end, idx);
}

int main() {
    scanf("%d %d", &n, &m);
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    
    for (int i = 0; i < m; i++) {
        int t, l, r;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &l, &r);
            update(1, 1, n, l, r);
        } else {
            scanf("%d", &l);
            printf("%d\n", query(1, 1, n, l));
        }
    }
    
    return 0;
}