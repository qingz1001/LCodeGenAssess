#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define MAX_SCORE 100

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

void calculateScore(TreeNode *root, int *score) {
    if (root == NULL) {
        score[root] = 1;
        return;
    }
    calculateScore(root->left, score);
    calculateScore(root->right, score);
    if (root->left != NULL && root->right != NULL) {
        score[root] = score[root->left] * score[root->right] + root->data;
    } else if (root->left != NULL) {
        score[root] = score[root->left] + root->data;
    } else if (root->right != NULL) {
        score[root] = score[root->right] + root->data;
    } else {
        score[root] = root->data;
    }
}

TreeNode* buildTree(int in[], int post[], int inStart, int inEnd, int *postIndex, int score[]) {
    if (inStart > inEnd) return NULL;
    int rootVal = post[*postIndex--];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = rootVal;
    int rootIndex;
    for (int i = inStart; i <= inEnd; i++) {
        if (in[i] == rootVal) {
            rootIndex = i;
            break;
        }
    }
    root->right = buildTree(in, post, rootIndex + 1, inEnd, postIndex, score);
    root->left = buildTree(in, post, inStart, rootIndex - 1, postIndex, score);
    return root;
}

void preOrderTraversal(TreeNode *root, int *result, int *index) {
    if (root == NULL) return;
    result[(*index)++] = root->data;
    preOrderTraversal(root->left, result, index);
    preOrderTraversal(root->right, result, index);
}

int main() {
    int n;
    scanf("%d", &n);
    int d[MAXN], score[MAXN * MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    int in[MAXN], post[MAXN];
    for (int i = 0; i < n; i++) {
        in[i] = i + 1;
        post[i] = n - i;
    }

    TreeNode* root = buildTree(in, post, 0, n - 1, &post[n - 1], score);

    printf("%d\n", score[root]);

    int result[MAXN], index = 0;
    preOrderTraversal(root, result, &index);
    for (int i = 0; i < n; i++) {
        printf("%d", result[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    free(root);
    return 0;
}