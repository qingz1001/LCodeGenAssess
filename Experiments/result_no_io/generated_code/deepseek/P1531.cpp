#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int max_score;
    int left, right;
} SegmentTreeNode;

SegmentTreeNode* buildSegmentTree(int* scores, int left, int right) {
    if (left > right) return NULL;

    SegmentTreeNode* node = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
    node->left = left;
    node->right = right;

    if (left == right) {
        node->max_score = scores[left];
    } else {
        int mid = left + (right - left) / 2;
        SegmentTreeNode* left_child = buildSegmentTree(scores, left, mid);
        SegmentTreeNode* right_child = buildSegmentTree(scores, mid + 1, right);
        node->max_score = MAX(left_child->max_score, right_child->max_score);
    }

    return node;
}

int query(SegmentTreeNode* node, int left, int right) {
    if (node->left == left && node->right == right) {
        return node->max_score;
    }

    int mid = node->left + (node->right - node->left) / 2;
    if (right <= mid) {
        return query(node + 1, left, right);
    } else if (left > mid) {
        return query(node + 2 * (mid - node->left + 1), left, right);
    } else {
        return MAX(query(node + 1, left, mid), query(node + 2 * (mid - node->left + 1), mid + 1, right));
    }
}

void update(SegmentTreeNode* node, int index, int new_score) {
    if (node->left == node->right) {
        node->max_score = new_score;
        return;
    }

    int mid = node->left + (node->right - node->left) / 2;
    if (index <= mid) {
        update(node + 1, index, new_score);
    } else {
        update(node + 2 * (mid - node->left + 1), index, new_score);
    }

    node->max_score = MAX(node[1].max_score, node[2 * (mid - node->left + 1)].max_score);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* scores = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    SegmentTreeNode* root = buildSegmentTree(scores, 0, n - 1);

    char operation;
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf(" %c %d %d", &operation, &a, &b);
        if (operation == 'Q') {
            printf("%d\n", query(root, a - 1, b - 1));
        } else if (operation == 'U') {
            if (scores[a - 1] < b) {
                scores[a - 1] = b;
                update(root, a - 1, b);
            }
        }
    }

    free(scores);
    free(root);

    return 0;
}