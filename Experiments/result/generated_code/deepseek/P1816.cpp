#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int query(int* st, int ql, int qr, int l, int r, int idx) {
    if (ql <= l && qr >= r) {
        return st[idx];
    }
    if (qr < l || ql > r) {
        return INT_MAX;
    }
    int mid = l + (r - l) / 2;
    return min(query(st, ql, qr, l, mid, 2 * idx + 1), query(st, ql, qr, mid + 1, r, 2 * idx + 2));
}

void build(int* arr, int* st, int l, int r, int idx) {
    if (l == r) {
        st[idx] = arr[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(arr, st, l, mid, 2 * idx + 1);
    build(arr, st, mid + 1, r, 2 * idx + 2);
    st[idx] = min(st[2 * idx + 1], st[2 * idx + 2]);
}

int* createSegmentTree(int* arr, int n) {
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    int* st = (int*)malloc(max_size * sizeof(int));
    build(arr, st, 0, n - 1, 0);
    return st;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int* accounts = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &accounts[i]);
    }

    int* st = createSegmentTree(accounts, m);

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d ", query(st, a - 1, b - 1, 0, m - 1, 0));
    }

    free(accounts);
    free(st);
    return 0;
}