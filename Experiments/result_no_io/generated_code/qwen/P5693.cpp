#include <stdio.h>
#include <stdlib.h>

#define MAXN 400005
#define BLOCK_SIZE 2000

typedef struct {
    int val;
    int lazy;
} Node;

Node tree[MAXN / BLOCK_SIZE];
int arr[MAXN];

void push(int idx, int left, int right) {
    if (tree[idx].lazy != 0) {
        tree[idx].val += (right - left + 1) * tree[idx].lazy;
        if (left != right) {
            tree[idx * 2].lazy += tree[idx].lazy;
            tree[idx * 2 + 1].lazy += tree[idx].lazy;
        }
        tree[idx].lazy = 0;
    }
}

int query(int idx, int left, int right, int ql, int qr) {
    push(idx, left, right);
    if (ql > right || qr < left) return 0;
    if (ql <= left && right <= qr) return tree[idx].val;
    int mid = (left + right) / 2;
    return query(idx * 2, left, mid, ql, qr) + query(idx * 2 + 1, mid + 1, right, ql, qr);
}

void update(int idx, int left, int right, int ql, int qr, int val) {
    push(idx, left, right);
    if (ql > right || qr < left) return;
    if (ql <= left && right <= qr) {
        tree[idx].val += (right - left + 1) * val;
        if (left != right) {
            tree[idx * 2].lazy += val;
            tree[idx * 2 + 1].lazy += val;
        }
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2, left, mid, ql, qr, val);
    update(idx * 2 + 1, mid + 1, right, ql, qr, val);
    tree[idx].val = tree[idx * 2].val + tree[idx * 2 + 1].val;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        tree[i / BLOCK_SIZE].val += arr[i];
    }

    while (q--) {
        int type, l, r, x;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &l, &r, &x);
            update(1, 0, n - 1, l - 1, r - 1, x);
        } else {
            scanf("%d %d", &l, &r);
            printf("%d\n", query(1, 0, n - 1, l - 1, r - 1));
        }
    }

    return 0;
}