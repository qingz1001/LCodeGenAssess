#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int l, r;
    int sum; // 区间内1的个数
    int max_len; // 区间内最长连续1的长度
    int lmax, rmax; // 从左端点开始和从右端点开始的最长连续1的长度
    int lazy; // 懒标记，-1表示无操作，0表示全0，1表示全1，2表示取反
} Node;

Node tree[4 * MAXN];
int arr[MAXN];

void push_up(int node) {
    int left = 2 * node, right = 2 * node + 1;
    tree[node].sum = tree[left].sum + tree[right].sum;
    tree[node].lmax = tree[left].lmax;
    if (tree[left].lmax == tree[left].r - tree[left].l + 1)
        tree[node].lmax += tree[right].lmax;
    tree[node].rmax = tree[right].rmax;
    if (tree[right].rmax == tree[right].r - tree[right].l + 1)
        tree[node].rmax += tree[left].rmax;
    tree[node].max_len = tree[left].rmax + tree[right].lmax;
    if (tree[left].max_len > tree[node].max_len)
        tree[node].max_len = tree[left].max_len;
    if (tree[right].max_len > tree[node].max_len)
        tree[node].max_len = tree[right].max_len;
}

void push_down(int node) {
    int left = 2 * node, right = 2 * node + 1;
    if (tree[node].lazy == 0) {
        tree[left].sum = tree[right].sum = 0;
        tree[left].lmax = tree[left].rmax = tree[left].max_len = 0;
        tree[right].lmax = tree[right].rmax = tree[right].max_len = 0;
    } else if (tree[node].lazy == 1) {
        tree[left].sum = tree[left].r - tree[left].l + 1;
        tree[right].sum = tree[right].r - tree[right].l + 1;
        tree[left].lmax = tree[left].rmax = tree[left].max_len = tree[left].r - tree[left].l + 1;
        tree[right].lmax = tree[right].rmax = tree[right].max_len = tree[right].r - tree[right].l + 1;
    } else if (tree[node].lazy == 2) {
        tree[left].sum = (tree[left].r - tree[left].l + 1) - tree[left].sum;
        tree[right].sum = (tree[right].r - tree[right].l + 1) - tree[right].sum;
        int lmax = tree[left].lmax, rmax = tree[left].rmax, max_len = tree[left].max_len;
        tree[left].lmax = tree[left].rmax = tree[left].max_len = (tree[left].r - tree[left].l + 1) - max_len;
        lmax = tree[right].lmax, rmax = tree[right].rmax, max_len = tree[right].max_len;
        tree[right].lmax = tree[right].rmax = tree[right].max_len = (tree[right].r - tree[right].l + 1) - max_len;
    }
    tree[left].lazy = tree[right].lazy = tree[node].lazy;
    tree[node].lazy = -1;
}

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    tree[node].lazy = -1;
    if (l == r) {
        tree[node].sum = arr[l];
        tree[node].lmax = tree[node].rmax = tree[node].max_len = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    push_up(node);
}

void update(int node, int l, int r, int type) {
    if (tree[node].l >= l && tree[node].r <= r) {
        if (type == 0) {
            tree[node].sum = 0;
            tree[node].lmax = tree[node].rmax = tree[node].max_len = 0;
            tree[node].lazy = 0;
        } else if (type == 1) {
            tree[node].sum = tree[node].r - tree[node].l + 1;
            tree[node].lmax = tree[node].rmax = tree[node].max_len = tree[node].r - tree[node].l + 1;
            tree[node].lazy = 1;
        } else if (type == 2) {
            tree[node].sum = (tree[node].r - tree[node].l + 1) - tree[node].sum;
            int lmax = tree[node].lmax, rmax = tree[node].rmax, max_len = tree[node].max_len;
            tree[node].lmax = tree[node].rmax = tree[node].max_len = (tree[node].r - tree[node].l + 1) - max_len;
            tree[node].lazy = 2;
        }
        return;
    }
    if (tree[node].lazy != -1) push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    if (l <= mid) update(2 * node, l, r, type);
    if (r > mid) update(2 * node + 1, l, r, type);
    push_up(node);
}

int query_sum(int node, int l, int r) {
    if (tree[node].l >= l && tree[node].r <= r) {
        return tree[node].sum;
    }
    if (tree[node].lazy != -1) push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    int sum = 0;
    if (l <= mid) sum += query_sum(2 * node, l, r);
    if (r > mid) sum += query_sum(2 * node + 1, l, r);
    return sum;
}

int query_max_len(int node, int l, int r) {
    if (tree[node].l >= l && tree[node].r <= r) {
        return tree[node].max_len;
    }
    if (tree[node].lazy != -1) push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    int max_len = 0;
    if (l <= mid) max_len = query_max_len(2 * node, l, r);
    if (r > mid) max_len = query_max_len(2 * node + 1, l, r);
    return max_len;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    build(1, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0 || op == 1 || op == 2) {
            update(1, l, r, op);
        } else if (op == 3) {
            printf("%d\n", query_sum(1, l, r));
        } else if (op == 4) {
            printf("%d\n", query_max_len(1, l, r));
        }
    }
    return 0;
}