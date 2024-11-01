#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return a < b ? a : b;
}

void buildSegmentTree(int *arr, int *tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(arr, tree, 2 * node, start, mid);
        buildSegmentTree(arr, tree, 2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

int querySegmentTree(int *tree, int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MAX;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int p1 = querySegmentTree(tree, 2 * node, start, mid, l, r);
    int p2 = querySegmentTree(tree, 2 * node + 1, mid + 1, end, l, r);
    return min(p1, p2);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int *arr = (int *)malloc((m + 1) * sizeof(int));
    for (int i = 1; i <= m; i++) {
        scanf("%d", &arr[i]);
    }

    int *tree = (int *)malloc(4 * (m + 1) * sizeof(int));
    buildSegmentTree(arr, tree, 1, 1, m);

    int a, b;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        if (i > 0) {
            printf(" ");
        }
        printf("%d", querySegmentTree(tree, 1, 1, m, a, b));
    }
    printf("\n");

    free(arr);
    free(tree);

    return 0;
}