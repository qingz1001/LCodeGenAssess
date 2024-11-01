#include <stdio.h>
#include <string.h>

#define MAXN 100005

int n, m;
int tree[MAXN * 4];
int lazy[MAXN * 4];

void push_down(int node, int left, int right) {
    if (lazy[node]) {
        int mid = (left + right) / 2;
        tree[node * 2] = (mid - left + 1) - tree[node * 2];
        tree[node * 2 + 1] = (right - mid) - tree[node * 2 + 1];
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
        lazy[node] = 0;
    }
}

void update(int node, int left, int right, int L, int R) {
    if (L <= left && right <= R) {
        tree[node] = (right - left + 1) - tree[node];
        lazy[node] ^= 1;
        return;
    }
    push_down(node, left, right);
    int mid = (left + right) / 2;
    if (L <= mid) update(node * 2, left, mid, L, R);
    if (R > mid) update(node * 2 + 1, mid + 1, right, L, R);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int left, int right, int pos) {
    if (left == right) return tree[node];
    push_down(node, left, right);
    int mid = (left + right) / 2;
    if (pos <= mid) return query(node * 2, left, mid, pos);
    else return query(node * 2 + 1, mid + 1, right, pos);
}

int main() {
    scanf("%d %d", &n, &m);
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    for (int i = 0; i < m; i++) {
        int t, L, R;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &L, &R);
            update(1, 1, n, L, R);
        } else {
            scanf("%d", &L);
            printf("%d\n", query(1, 1, n, L));
        }
    }

    return 0;
}