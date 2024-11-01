#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int *arr = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
    }

    int *tree = (int *)malloc(4 * m * sizeof(int));

    // Build the segment tree
    void build(int *tree, int *arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(tree, arr, 2 * node + 1, start, mid);
            build(tree, arr, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    build(tree, arr, 0, 0, m - 1);

    // Query the segment tree
    int query(int *tree, int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return INT_MAX;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(tree, 2 * node + 1, start, mid, L, R);
        int p2 = query(tree, 2 * node + 2, mid + 1, end, L, R);
        return min(p1, p2);
    }

    // Process each query
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d ", query(tree, 0, 0, m - 1, a - 1, b - 1));
    }

    free(arr);
    free(tree);
    return 0;
}