#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int max(int a, int b) {
    return a > b ? a : b;
}

void build_tree(int* tree, int* arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build_tree(tree, arr, 2 * node, start, mid);
    build_tree(tree, arr, 2 * node + 1, mid + 1, end);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

void update_tree(int* tree, int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid)
        update_tree(tree, 2 * node, start, mid, idx, val);
    else
        update_tree(tree, 2 * node + 1, mid + 1, end, idx, val);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

int query_tree(int* tree, int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return -1;
    if (l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int left = query_tree(tree, 2 * node, start, mid, l, r);
    int right = query_tree(tree, 2 * node + 1, mid + 1, end, l, r);
    return max(left, right);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* scores = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    int* tree = (int*)malloc(4 * n * sizeof(int));
    build_tree(tree, scores, 1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);

        if (op == 'Q') {
            printf("%d\n", query_tree(tree, 1, 0, n - 1, a - 1, b - 1));
        } else if (op == 'U') {
            if (scores[a - 1] < b) {
                scores[a - 1] = b;
                update_tree(tree, 1, 0, n - 1, a - 1, b);
            }
        }
    }

    free(scores);
    free(tree);
    return 0;
}