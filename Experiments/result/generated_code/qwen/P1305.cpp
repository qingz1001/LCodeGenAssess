#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertNode(TreeNode** root, char parent, char leftChild, char rightChild) {
    if (*root == NULL) {
        if (parent != '*') {
            *root = createNode(parent);
            insertNode(&(*root)->left, leftChild, '*', '*');
            insertNode(&(*root)->right, rightChild, '*', '*');
        }
    } else {
        if ((*root)->data == parent) {
            if (leftChild != '*') {
                (*root)->left = createNode(leftChild);
            }
            if (rightChild != '*') {
                (*root)->right = createNode(rightChild);
            }
        } else {
            insertNode(&(*root)->left, parent, leftChild, rightChild);
            insertNode(&(*root)->right, parent, leftChild, rightChild);
        }
    }
}

void preOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        char parent, leftChild, rightChild;
        scanf(" %c %c %c", &parent, &leftChild, &rightChild);
        insertNode(&root, parent, leftChild, rightChild);
    }

    preOrderTraversal(root);
    printf("\n");

    return 0;
}