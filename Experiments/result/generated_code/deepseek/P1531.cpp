#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int max;
    int start;
    int end;
} SegmentTreeNode;

SegmentTreeNode* buildSegmentTree(int* arr, int start, int end) {
    if (start > end) return NULL;

    SegmentTreeNode* node = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
    node->start = start;
    node->end = end;

    if (start == end) {
        node->max = arr[start];
    } else {
        int mid = (start + end) / 2;
        SegmentTreeNode* left = buildSegmentTree(arr, start, mid);
        SegmentTreeNode* right = buildSegmentTree(arr, mid + 1, end);
        node->max = MAX(left->max, right->max);
        free(left);
        free(right);
    }
    return node;
}

int querySegmentTree(SegmentTreeNode* root, int start, int end) {
    if (root == NULL || start > root->end || end < root->start) return -1;
    if (start <= root->start && end >= root->end) return root->max;

    int mid = (root->start + root->end) / 2;
    if (end <= mid) {
        return querySegmentTree(root, start, end);
    } else if (start > mid) {
        return querySegmentTree(root, start, end);
    } else {
        return MAX(querySegmentTree(root, start, mid), querySegmentTree(root, mid + 1, end));
    }
}

void updateSegmentTree(SegmentTreeNode* root, int index, int value) {
    if (root == NULL || index < root->start || index > root->end) return;
    if (root->start == root->end) {
        root->max = value;
        return;
    }

    int mid = (root->start + root->end) / 2;
    if (index <= mid) {
        updateSegmentTree(root, index, value);
    } else {
        updateSegmentTree(root, index, value);
    }
    root->max = MAX(root->max, value);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* grades = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &grades[i]);
    }

    SegmentTreeNode* root = buildSegmentTree(grades, 0, n - 1);

    char operation;
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf(" %c %d %d", &operation, &a, &b);
        if (operation == 'Q') {
            printf("%d\n", querySegmentTree(root, a - 1, b - 1));
        } else if (operation == 'U') {
            if (grades[a - 1] < b) {
                grades[a - 1] = b;
                updateSegmentTree(root, a - 1, b);
            }
        }
    }

    free(grades);
    return 0;
}