#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char root;
    scanf(" %c", &root);
    TreeNode* tree = createNode(root);

    for (int i = 0; i < n - 1; i++) {
        char node, left, right;
        scanf(" %c %c %c", &node, &left, &right);
        TreeNode* current = createNode(node);
        if (left != '*') {
            current->left = createNode(left);
        }
        if (right != '*') {
            current->right = createNode(right);
        }
        // Assuming that the tree is being built by adding nodes one by one and each node is guaranteed to be a child of the root or a previously added node.
    }

    preOrder(tree);
    printf("\n");
    return 0;
}